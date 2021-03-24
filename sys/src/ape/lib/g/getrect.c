#include <libg.h>

static Cursor sweep={
	{-7, -7},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x07,
	 0xE0, 0x07, 0xE0, 0x07, 0xE3, 0xF7, 0xE3, 0xF7,
	 0xE3, 0xE7, 0xE3, 0xF7, 0xE3, 0xFF, 0xE3, 0x7F,
	 0xE0, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,},
	{0x00, 0x00, 0x7F, 0xFE, 0x40, 0x02, 0x40, 0x02,
	 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x41, 0xE2,
	 0x41, 0xC2, 0x41, 0xE2, 0x41, 0x72, 0x40, 0x38,
	 0x40, 0x1C, 0x40, 0x0E, 0x7F, 0xE6, 0x00, 0x00,}
};

Rectangle
getrect(int but, Mouse *m){
	Rectangle r, rc;

	but = 1<<(but-1);
	cursorswitch(&sweep);
	while(m->buttons)
		*m = emouse();
	while(!(m->buttons & but)){
		*m = emouse();
		if(m->buttons & (7^but))
			goto Return;
	}
	r.min = m->xy;
	r.max = m->xy;
	do{
		rc = rcanon(r);
		border(&screen, rc, 2, F&~D);
		*m = emouse();
		border(&screen, rc, 2, F&~D);
		r.max = m->xy;
	}while(m->buttons & but);

    Return:
	cursorswitch((Cursor *)0);
	if(m->buttons & (7^but)){
		rc.min.x = rc.max.x = 0;
		while(m->buttons)
			*m = emouse();
	}
	return rc;
}