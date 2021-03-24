#include	"u.h"
#include	"../port/lib.h"
#include	"mem.h"
#include	"dat.h"
#include	"fns.h"
#include	"../port/error.h"

#define	Image	IMAGE
#include	<draw.h>
#include	<memdraw.h>
#include	<cursor.h>
#include	"screen.h"

typedef struct Mouseinfo	Mouseinfo;
typedef struct Mousestate	Mousestate;

struct Mousestate
{
	Point	xy;			/* mouse.xy */
	int	buttons;		/* mouse.buttons */
	ulong	counter;	/* increments every update */
	ulong	msec;	/* time of last event */
};

struct Mouseinfo
{
	Mousestate;
	int	dx;
	int	dy;
	int	track;		/* dx & dy updated */
	int	redraw;		/* update cursor on screen */
	ulong	lastcounter;	/* value when /dev/mouse read */
	Rendez	r;
	Ref;
	QLock;
	int	open;
	int	inopen;
	int	acceleration;
	int	maxacc;
	Mousestate 	queue[16];	/* circular buffer of click events */
	int	ri;	/* read index into queue */
	int	wi;	/* write index into queue */
	uchar	qfull;	/* queue is full */
};

Mouseinfo	mouse;
Cursorinfo	cursor;
int		mouseshifted;
Cursor		curs;

void	Cursortocursor(Cursor*);
int	mousechanged(void*);
static void mouseclock(void);

enum{
	Qdir,
	Qcursor,
	Qmouse,
	Qmousein,
	Qmousectl,
};

static Dirtab mousedir[]={
	"cursor",	{Qcursor},	0,			0666,
	"mouse",	{Qmouse},	0,			0666,
	"mousein",	{Qmousein},	0,			0220,
	"mousectl",	{Qmousectl},	0,			0220,
};

static uchar buttonmap[8] = {
	0, 1, 2, 3, 4, 5, 6, 7,
};
static int mouseswap;

extern	Memimage*	gscreen;

static void
mousereset(void)
{
	if(!conf.monitor)
		return;

	curs = arrow;
	Cursortocursor(&arrow);
	addclock0link(mouseclock);
}

static void
mouseinit(void)
{
	if(!conf.monitor)
		return;

	cursoron(1);
}

static Chan*
mouseattach(char *spec)
{
	if(!conf.monitor)
		error(Egreg);
	return devattach('m', spec);
}

static Chan*
mouseclone(Chan *c, Chan *nc)
{
	nc = devclone(c, nc);
	if(c->qid.path != CHDIR)
		incref(&mouse);
	return nc;
}

static int
mousewalk(Chan *c, char *name)
{
	return devwalk(c, name, mousedir, nelem(mousedir), devgen);
}

static void
mousestat(Chan *c, char *db)
{
	devstat(c, db, mousedir, nelem(mousedir), devgen);
}

static Chan*
mouseopen(Chan *c, int omode)
{
	switch(c->qid.path){
	case CHDIR:
		if(omode != OREAD)
			error(Eperm);
		break;
	case Qmouse:
		lock(&mouse);
		if(mouse.open){
			unlock(&mouse);
			error(Einuse);
		}
		mouse.open = 1;
		mouse.ref++;
		unlock(&mouse);
		break;
	case Qmousein:
	/*	error("disabled");	*/
		lock(&mouse);
		if(mouse.inopen){
			unlock(&mouse);
			error(Einuse);
		}
		mouse.inopen = 1;
		unlock(&mouse);
		break;
	default:
		incref(&mouse);
	}
	c->mode = openmode(omode);
	c->flag |= COPEN;
	c->offset = 0;
	return c;
}

static void
mousecreate(Chan*, char*, int, ulong)
{
	if(!conf.monitor)
		error(Egreg);
	error(Eperm);
}

static void
mouseclose(Chan *c)
{
	if(c->qid.path!=CHDIR && (c->flag&COPEN)){
		lock(&mouse);
		if(c->qid.path == Qmouse)
			mouse.open = 0;
		else if(c->qid.path == Qmousein){
			mouse.inopen = 0;
			unlock(&mouse);
			return;
		}
		if(--mouse.ref == 0){
			cursoroff(1);
			curs = arrow;
			Cursortocursor(&arrow);
			cursoron(1);
		}
		unlock(&mouse);
	}
}


static long
mouseread(Chan *c, void *va, long n, vlong off)
{
	char buf[4*12+1];
	uchar *p;
	static int map[8] = {0, 4, 2, 6, 1, 5, 3, 7 };
	ulong offset = off;
	Mousestate m;
	int b;

	p = va;
	switch(c->qid.path){
	case CHDIR:
		return devdirread(c, va, n, mousedir, nelem(mousedir), devgen);

	case Qcursor:
		if(offset != 0)
			return 0;
		if(n < 2*4+2*2*16)
			error(Eshort);
		n = 2*4+2*2*16;
		lock(&cursor);
		BPLONG(p+0, curs.offset.x);
		BPLONG(p+4, curs.offset.y);
		memmove(p+8, curs.clr, 2*16);
		memmove(p+40, curs.set, 2*16);
		unlock(&cursor);
		return n;

	case Qmouse:
		while(mousechanged(0) == 0)
			sleep(&mouse.r, mousechanged, 0);

		mouse.qfull = 0;

		/*
		 * No lock of the indicies is necessary here, because ri is only
		 * updated by us, and there is only one mouse reader
		 * at a time.  I suppose that more than one process
		 * could try to read the fd at one time, but such behavior
		 * is degenerate and already violates the calling
		 * conventions for sleep above.
		 */
		if(mouse.ri != mouse.wi) {
			m = mouse.queue[mouse.ri];
			if(++mouse.ri == nelem(mouse.queue))
				mouse.ri = 0;
		} else {
			while(!canlock(&cursor))
				tsleep(&up->sleep, return0, 0, TK2MS(1));
	
			m = mouse.Mousestate;
			unlock(&cursor);
		}

		b = buttonmap[m.buttons&7];
		/* put buttons 4 and 5 back in */
		b |= m.buttons & (3<<3);
		sprint(buf, "m%11d %11d %11d %11lud",
			m.xy.x, m.xy.y,
			b,
			m.msec);
		mouse.lastcounter = m.counter;
		if(n > 1+4*12)
			n = 1+4*12;
		memmove(va, buf, n);
		return n;
	}
	return 0;
}

static void
setbuttonmap(char* map)
{
	int i, x, one, two, three;

	one = two = three = 0;
	for(i = 0; i < 3; i++){
		if(map[i] == 0)
			error(Ebadarg);
		if(map[i] == '1'){
			if(one)
				error(Ebadarg);
			one = 1<<i;
		}
		else if(map[i] == '2'){
			if(two)
				error(Ebadarg);
			two = 1<<i;
		}
		else if(map[i] == '3'){
			if(three)
				error(Ebadarg);
			three = 1<<i;
		}
		else
			error(Ebadarg);
	}
	if(map[i])
		error(Ebadarg);

	memset(buttonmap, 0, 8);
	for(i = 0; i < 8; i++){
		x = 0;
		if(i & 1)
			x |= one;
		if(i & 2)
			x |= two;
		if(i & 4)
			x |= three;
		buttonmap[x] = i;
	}
}

static long
mousewrite(Chan *c, void *va, long n, vlong)
{
	char *p;
	Point pt;
	char buf[64], *field[3];
	int nf, b;

	p = va;
	switch(c->qid.path){
	case CHDIR:
		error(Eisdir);

	case Qcursor:
		cursoroff(1);
		if(n < 2*4+2*2*16){
			curs = arrow;
			Cursortocursor(&arrow);
		}else{
			n = 2*4+2*2*16;
			curs.offset.x = BGLONG(p+0);
			curs.offset.y = BGLONG(p+4);
			memmove(curs.clr, p+8, 2*16);
			memmove(curs.set, p+40, 2*16);
			Cursortocursor(&curs);
		}
		qlock(&mouse);
		mouse.redraw = 1;
		mouseclock();
		qunlock(&mouse);
		cursoron(1);
		return n;

	case Qmousectl:
		if(n >= sizeof(buf))
			n = sizeof(buf)-1;
		strncpy(buf, va, n);
		if(buf[n - 1] == '\n')
			buf[n-1] = 0;
		else
			buf[n] = 0;
		nf = getfields(buf, field, 3, 1, " ");
		if(strcmp(field[0], "swap") == 0){
			if(mouseswap)
				setbuttonmap("123");
			else
				setbuttonmap("321");
			mouseswap ^= 1;
		}
		else if(strcmp(field[0], "buttonmap") == 0){
			if(nf == 1)
				setbuttonmap("123");
			else
				setbuttonmap(field[1]);
		}
		else
			mousectl(field, nf);
		return n;

	case Qmousein:
		if(n > sizeof buf-1)
			n = sizeof buf -1;
		memmove(buf, va, n);
		buf[n] = 0;
		p = 0;
		pt.x = strtol(buf+1, &p, 0);
		if(p == 0)
			error(Eshort);
		pt.y = strtol(p, &p, 0);
		if(p == 0)
			error(Eshort);
		b = strtol(p, &p, 0);
		mousetrack(b, pt.x, pt.y);
		return n;
		
	case Qmouse:
		if(n > sizeof buf-1)
			n = sizeof buf -1;
		memmove(buf, va, n);
		buf[n] = 0;
		p = 0;
		pt.x = strtoul(buf+1, &p, 0);
		if(p == 0)
			error(Eshort);
		pt.y = strtoul(p, 0, 0);
		qlock(&mouse);
		if(ptinrect(pt, gscreen->r)){
			mouse.xy = pt;
			mouse.redraw = 1;
			mouse.track = 1;
			mouseclock();
		}
		qunlock(&mouse);
		return n;
	}

	error(Egreg);
	return -1;
}

Dev mousedevtab = {
	'm',
	"mouse",

	mousereset,
	mouseinit,
	mouseattach,
	mouseclone,
	mousewalk,
	mousestat,
	mouseopen,
	mousecreate,
	mouseclose,
	mouseread,
	devbread,
	mousewrite,
	devbwrite,
	devremove,
	devwstat,
};

void
Cursortocursor(Cursor *c)
{
	lock(&cursor);
	memmove(&cursor.Cursor, c, sizeof(Cursor));
	setcursor(c);
	unlock(&cursor);
}


/*
 *  called by the clock routine to redraw the cursor
 */
static void
mouseclock(void)
{
	if(mouse.track){
		mousetrack(mouse.buttons, mouse.dx, mouse.dy);
		mouse.track = 0;
		mouse.dx = 0;
		mouse.dy = 0;
	}
	if(mouse.redraw && canlock(&cursor)){
		mouse.redraw = 0;
		cursoroff(0);
		mouse.redraw = cursoron(0);
		unlock(&cursor);
	}
	drawactive(0);
}

static int
scale(int x)
{
	int sign = 1;

	if(x < 0){
		sign = -1;
		x = -x;
	}
	switch(x){
	case 0:
	case 1:
	case 2:
	case 3:
		break;
	case 4:
		x = 6 + (mouse.acceleration>>2);
		break;
	case 5:
		x = 9 + (mouse.acceleration>>1);
		break;
	default:
		x *= mouse.maxacc;
		break;
	}
	return sign*x;
}

/*
 *  called at interrupt level to update the structure and
 *  awaken any waiting procs.
 */
void
mousetrack(int b, int dx, int dy)
{
	int x, y, lastb;

	if(gscreen==nil)
		return;

	if(mouse.acceleration){
		dx = scale(dx);
		dy = scale(dy);
	}
	x = mouse.xy.x + dx;
	if(x < gscreen->r.min.x)
		x = gscreen->r.min.x;
	if(x >= gscreen->r.max.x)
		x = gscreen->r.max.x;
	y = mouse.xy.y + dy;
	if(y < gscreen->r.min.y)
		y = gscreen->r.min.y;
	if(y >= gscreen->r.max.y)
		y = gscreen->r.max.y;

	lastb = mouse.buttons;
	mouse.xy = Pt(x, y);
	mouse.buttons = b;
	mouse.redraw = 1;
	mouse.counter++;
	mouse.msec = TK2MS(MACHP(0)->ticks);

	/*
	 * if the queue fills, we discard the entire queue and don't
	 * queue any more events until a reader polls the mouse.
	 */
	if(!mouse.qfull && lastb != b) {	/* add to ring */
		mouse.queue[mouse.wi] = mouse.Mousestate;
		if(++mouse.wi == nelem(mouse.queue))
			mouse.wi = 0;
		if(mouse.wi == mouse.ri)
			mouse.qfull = 1;
	}
	wakeup(&mouse.r);
	drawactive(1);
}

/*
 *  microsoft 3 button, 7 bit bytes
 *
 *	byte 0 -	1  L  R Y7 Y6 X7 X6
 *	byte 1 -	0 X5 X4 X3 X2 X1 X0
 *	byte 2 -	0 Y5 Y4 Y3 Y2 Y1 Y0
 *	byte 3 -	0  M  x  x  x  x  x	(optional)
 *
 *  shift & right button is the same as middle button (for 2 button mice)
 */
int
m3mouseputc(Queue*, int c)
{
	static uchar msg[3];
	static int nb;
	static int middle;
	static uchar b[] = { 0, 4, 1, 5, 0, 2, 1, 3 };
	short x;
	int dx, dy, newbuttons;

	if(nb==0){
		/*
		 * an extra byte comes for middle button motion.
		 * only two possible values for the extra byte.
		 */
		if(c == 0x00 || c == 0x20){
			/* an extra byte gets sent for the middle button */
			middle = (c&0x20) ? 2 : 0;
			newbuttons = (mouse.buttons & ~2) | middle;
			mousetrack(newbuttons, 0, 0);
			return 0;
		}
	}
	msg[nb] = c;
	if(++nb == 3){
		nb = 0;
		newbuttons = middle | b[(msg[0]>>4)&3 | (mouseshifted ? 4 : 0)];
		x = (msg[0]&0x3)<<14;
		dx = (x>>8) | msg[1];
		x = (msg[0]&0xc)<<12;
		dy = (x>>8) | msg[2];
		mousetrack(newbuttons, dx, dy);
	}
	return 0;
}

/*
 *  Logitech 5 byte packed binary mouse format, 8 bit bytes
 *
 *  shift & right button is the same as middle button (for 2 button mice)
 */
int
mouseputc(Queue*, int c)
{
	static short msg[5];
	static int nb;
	static uchar b[] = {0, 4, 2, 6, 1, 5, 3, 7, 0, 2, 2, 6, 1, 3, 3, 7};
	int dx, dy, newbuttons;

	if((c&0xF0) == 0x80)
		nb=0;
	msg[nb] = c;
	if(c & 0x80)
		msg[nb] |= ~0xFF;	/* sign extend */
	if(++nb == 5){
		newbuttons = b[((msg[0]&7)^7) | (mouseshifted ? 8 : 0)];
		dx = msg[1]+msg[3];
		dy = -(msg[2]+msg[4]);
		mousetrack(newbuttons, dx, dy);
		nb = 0;
	}
	return 0;
}

int
mousechanged(void*)
{
	return mouse.lastcounter != mouse.counter;
}

Point
mousexy(void)
{
	return mouse.xy;
}

void
mouseaccelerate(int x)
{
	mouse.acceleration = x;
	if(mouse.acceleration < 3)
		mouse.maxacc = 2;
	else
		mouse.maxacc = mouse.acceleration;
}
