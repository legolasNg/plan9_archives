#include <u.h>
#include <libc.h>
#include <bio.h>
#include <mach.h>
#include <ctype.h>
#define Extern extern
#include "3210.h"

void
dobplist(void)
{
	Breakpoint *b;
	char buf[128];

	for(b = bplist; b; b = b->next) {
		symoff(buf, sizeof buf, b->addr, CANY);
		switch(b->type) {
		case Instruction:
			Bprint(bioout, "0x%lux,%d:b %d done, at %s\n",
				b->addr, b->count, b->done, buf);
			break;

		case Access:
			Bprint(bioout, "0x%lux,%d:ba %d done, at %s\n",
				b->addr, b->count, b->done, buf);
			break;

		case Read:
			Bprint(bioout, "0x%lux,%d:br %d done, at %s\n",
				b->addr, b->count, b->done, buf);
			break;

		case Write:
			Bprint(bioout, "0x%lux,%d:bw %d done, at %s\n",
				b->addr, b->count, b->done, buf);
			break;

		case Equal:
			Bprint(bioout, "0x%lux,%d:be at %s\n",
				b->addr, b->count, buf);
			break;
		}
	}
}

void
breakpoint(char *cp)
{
	Breakpoint *b;
	int type;

	cp = nextc(cp);
	type = Instruction;
	switch(*cp) {
	case 'r':
		membpt++;
		type = Read;
		break;
	case 'a':
		membpt++;
		type = Access;
		break;
	case 'w':
		membpt++;
		type = Write;
		break;
	case 'e':
		membpt++;
		type = Equal;
		break;
	}
	b = emalloc(sizeof(Breakpoint));
	b->addr = dot;
	b->type = type;
	b->count = cmdcount;
	b->done = cmdcount;

	b->next = bplist;
	bplist = b;
}

void
delbpt(void)
{
	Breakpoint *b, **l;
	ulong baddr;

	baddr = dot;
	l = &bplist;
	for(b = *l; b; b = b->next) {
		if(b->addr == baddr) {
			if(b->type != Instruction)
				membpt++;
			*l = b->next;
			free(b);
			return;
		}
		l = &b->next;	
	}

	Bprint(bioout, "no breakpoint\n");
}

void
brkchk(ulong addr, int type)
{
	Breakpoint *b;

	for(b = bplist; b; b = b->next) {
		if(b->addr == addr && (b->type&type)) {
			if(b->type == Equal && getmem_4(addr) == b->count) {
				count = 1;
				atbpt = 1;
				return;
			}
			if(--b->done == 0) {
				b->done = b->count;
				count = 1;
				atbpt = 1;
				return;
			}
		}
	}	
}
