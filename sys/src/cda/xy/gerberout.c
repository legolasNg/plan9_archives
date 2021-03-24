#include <u.h>
#include <libc.h>
#include <libg.h>
#include <bio.h>
#include "dat.h"
#include "fns.h"

static void	displayfn(void*, void*);
static int	xsidecompare(Side**, Side**);
static int	ysidecompare(Side**, Side**);

static Sym *	layer;
static int	sense;

static Clump *	goo;
static Clump *	rects;
static Rcomp *	rhead;
static Rcomp *	rtail;

void
gerberout(void)
{
	Side *s, *sprev, *head; Clump *xp;
	int xesize, *xedge, nxe;
	int i, y0, y1, ymin, ymax;
	int owind, wind = 0;

	if(goo == 0 || goo->n == 0){
		fprint(2, "gerberout: no goo to mash\n");
		return;
	}

	xesize = 32;
	xedge = malloc(xesize*sizeof(int));

	qsort(goo->o, goo->n, sizeof(Side *), ysidecompare);

	head = goo->o[0];
	ymin = head->ymin;
	ymax = head->ymax;
	for(sprev=head, i=1; i<goo->n; sprev=s, i++){
		s = goo->o[i];
		sprev->next = s;
		if(s->ymax > ymax)
			ymax = s->ymax;
	}
	sprev->next = 0;
	if(debug)
		Bprint(&out, "ymin=%d, ymax=%d\n", ymin, ymax);
	if(debug>1)for(i=0; i<goo->n; i++){
		s = goo->o[i];
		Bprint(&out, "%d %c %d [%d %d)\n",
			i, (s->sense>0?'+':'-'), s->x, s->ymin, s->ymax);
	}
	xp = new(CLUMP);
	rects = new(CLUMP);
	for(y0 = ymin; y0 < ymax; y0 = y1){
		xp->n = 0;
		for(sprev=0, s=head; s; s=s->next){
			if(s->ymin > y0)
				break;
			if(y0 >= s->ymax){
				if(sprev)
					sprev->next = s->next;
				else
					head = s->next;
				continue;
			}
			wrclump(xp, s);
			sprev = s;
		}
		y1 = s ? s->ymin : ymax;
		for(i=0; i<xp->n; i++){
			s = xp->o[i];
			if(y0 < s->ymin && s->ymin < y1){
				y1 = s->ymin;
				break;
			}
			if(y0 < s->ymax && s->ymax < y1)
				y1 = s->ymax;
		}
		if(debug>1)
			Bprint(&out, "[%d, %d)\n", y0, y1);
		qsort(xp->o, xp->n, sizeof(Side *), xsidecompare);
		if(xp->size > xesize){
			xesize = xp->size;
			free(xedge);
			xedge = malloc(xesize*sizeof(int));
		}
		nxe = 0;
		for(i=0; i<xp->n; i++){
			s = xp->o[i];
			if(debug>1)
				Bprint(&out, "\t%d %c %d [%d %d)\n", i,
					(s->sense>0?'+':'-'), s->x,
					s->ymin, s->ymax);
			owind = wind;
			wind += s->sense;
			if((owind <= 0) == (wind <= 0))
				continue;
			if(nxe == 0 || s->x != xedge[nxe-1]){
				xedge[nxe++] = s->x;
				continue;
			}
			if(((nxe&1) == 0) != (wind <= 0))
				--nxe;
		}
		if(wind != 0)
			error("winding number botch");
		for(i=0; i<nxe; i+=2){
			addrect(Rxy(xedge[i], y0, xedge[i+1], y1));
		}
	}
}

void
addrect(Rectangle rn)
{
	Rcomp *r, *rprev;

	for(rprev=0, r=rhead; r; r=r->next){
		if(rn.min.y > r->max.y){
			if(rprev)
				rprev->next = r->next;
			else
				rhead = r->next;
			continue;
		}
		rprev = r;
		if(rn.min.x != r->min.x || rn.max.x != r->max.x)
			continue;
		if(rn.min.y != r->max.y)
			continue;
		r->max.y = rn.max.y;
		return;
	}
	r = new(RCOMP);
	wrclump(rects, r);
	r->next = 0;
	r->min = rn.min;
	r->max = rn.max;
	if(rtail)
		rtail->next = r;
	else
		rhead = r;
	rtail = r;
}

static int
ysidecompare(Side **sp0, Side **sp1)
{
	Side *s0 = *sp0, *s1 = *sp1;
	int t;

	if(t = s0->ymin - s1->ymin)	/* assign = */
		return t;
	return s0->x - s1->x;
}

static int
xsidecompare(Side **sp0, Side **sp1)
{
	Side *s0 = *sp0, *s1 = *sp1;

	return s0->x - s1->x;
}
