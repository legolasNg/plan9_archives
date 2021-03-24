#include <u.h>
#include <libc.h>
#include <bio.h>
#include <mach.h>
#define Extern extern
#include "3210.h"

Inst itab[] = {
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Isyscall,	Dsyscall,	"syscall",	Tsys},
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Idecgoto,	Ddecgoto,	"decgoto",	Tdecgoto},
	{Idecgoto,	Ddecgoto,	"decgoto",	Tdecgoto},
	{Icall,		Dcall,		"call",		Tcall},
	{Icall,		Dcall,		"call",		Tcall},
	{Iaddi,		Daddi,		"addi",		Taddi},
	{Iaddi,		Daddi,		"addi",		Taddi},
	{Icalu,		Dcalu,		"calu",		Tarith},
	{Ialui,		Dalui,		"alui",		Tarith},
	{Imovi,		Dmovi,		"move",		Tmem},
	{Imovi,		Dmovi,		"move",		Tmem},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifmadd,	Dfmadd,		"mult add",	Tfloat},
	{Ifspecial,	Dfspecial,	"float",	Tfspec},
	{Ifspecial,	Dfspecial,	"float",	Tfspec},
	{Ifspecial,	Dfspecial,	"float",	Tfspec},
	{Ifspecial,	Dfspecial,	"float",	Tfspec},
	{Icgoto,	Dcgoto,		"cond goto",	Tcgoto},
	{Icgoto,	Dcgoto,		"cond goto",	Tcgoto},
	{Icgoto,	Dcgoto,		"cond goto",	Tcgoto},
	{Icgoto,	Dcgoto,		"cond goto",	Tcgoto},
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Iundef,	Dundef,		"reserved",	Tillegal},
	{Idoi,		Ddoi,		"doi",		Tdo},
	{Ido,		Ddo,		"do",		Tdo},
	{Ishiftor,	Dshiftor,	"shift or",	Tshiftor},
	{Ishiftor,	Dshiftor,	"shift or",	Tshiftor},
	{Iaddi,		Daddi,		"addi",		Taddi},
	{Iaddi,		Daddi,		"addi",		Taddi},
	{Icalu,		Dcalu,		"calu",		Tarith},
	{Ialui,		Dalui,		"alui",		Tarith},
	{Imove,		Dmove,		"moverio",	Tmem},
	{Imovio,	Dmovio,		"moveiom",	Tmem},
	0
};