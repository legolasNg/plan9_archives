#include <u.h>
#include <libc.h>
# include "stdio.h"
# include "defines.h"
# include "object.h"
# include "operator.h"

struct oobject Op_tab[] = {
{OB_OPERATOR, XA_EXECUTABLE, trapOP},
{OB_OPERATOR, XA_EXECUTABLE, showOP},
{OB_OPERATOR, XA_EXECUTABLE, movetoOP},
{OB_OPERATOR, XA_EXECUTABLE, transformOP},
{OB_OPERATOR, XA_EXECUTABLE, gsaveOP},
{OB_OPERATOR, XA_EXECUTABLE, grestoreOP},
{OB_OPERATOR, XA_EXECUTABLE, currentpointOP},
{OB_OPERATOR, XA_EXECUTABLE, equalsOP},
{OB_OPERATOR, XA_EXECUTABLE, absOP},
{OB_OPERATOR, XA_EXECUTABLE, addOP},
{OB_OPERATOR, XA_EXECUTABLE, atanOP},
{OB_OPERATOR, XA_EXECUTABLE, ceilingOP},
{OB_OPERATOR, XA_EXECUTABLE, cosOP},
{OB_OPERATOR, XA_EXECUTABLE, divOP},
{OB_OPERATOR, XA_EXECUTABLE, expOP},
{OB_OPERATOR, XA_EXECUTABLE, floorOP},
{OB_OPERATOR, XA_EXECUTABLE, idivOP},
{OB_OPERATOR, XA_EXECUTABLE, lnOP},
{OB_OPERATOR, XA_EXECUTABLE, logOP},
{OB_OPERATOR, XA_EXECUTABLE, modOP},
{OB_OPERATOR, XA_EXECUTABLE, mulOP},
{OB_OPERATOR, XA_EXECUTABLE, negOP},
{OB_OPERATOR, XA_EXECUTABLE, randOP},
{OB_OPERATOR, XA_EXECUTABLE, roundOP},
{OB_OPERATOR, XA_EXECUTABLE, rrandOP},
{OB_OPERATOR, XA_EXECUTABLE, sinOP},
{OB_OPERATOR, XA_EXECUTABLE, sqrtOP},
{OB_OPERATOR, XA_EXECUTABLE, subOP},
{OB_OPERATOR, XA_EXECUTABLE, srandOP},
{OB_OPERATOR, XA_EXECUTABLE, truncateOP},
{OB_OPERATOR, XA_EXECUTABLE, eqOP},
{OB_OPERATOR, XA_EXECUTABLE, neOP},
{OB_OPERATOR, XA_EXECUTABLE, geOP},
{OB_OPERATOR, XA_EXECUTABLE, gtOP},
{OB_OPERATOR, XA_EXECUTABLE, leOP},
{OB_OPERATOR, XA_EXECUTABLE, ltOP},
{OB_OPERATOR, XA_EXECUTABLE, andOP},
{OB_OPERATOR, XA_EXECUTABLE, notOP},
{OB_OPERATOR, XA_EXECUTABLE, orOP},
{OB_OPERATOR, XA_EXECUTABLE, xorOP},
{OB_OPERATOR, XA_EXECUTABLE, bitshiftOP},
{OB_OPERATOR, XA_EXECUTABLE, beginOP},
{OB_OPERATOR, XA_EXECUTABLE, endOP},
{OB_OPERATOR, XA_EXECUTABLE, dictOP},
{OB_OPERATOR, XA_EXECUTABLE, lengthOP},
{OB_OPERATOR, XA_EXECUTABLE, maxlengthOP},
{OB_OPERATOR, XA_EXECUTABLE, popOP},
{OB_OPERATOR, XA_EXECUTABLE, exchOP},
{OB_OPERATOR, XA_EXECUTABLE, dupOP},
{OB_OPERATOR, XA_EXECUTABLE, copyOP},
{OB_OPERATOR, XA_EXECUTABLE, indexOP},
{OB_OPERATOR, XA_EXECUTABLE, rollOP},
{OB_OPERATOR, XA_EXECUTABLE, clearOP},
{OB_OPERATOR, XA_EXECUTABLE, countOP},
{OB_OPERATOR, XA_EXECUTABLE, markOP},
{OB_OPERATOR, XA_EXECUTABLE, markOP},
{OB_OPERATOR, XA_EXECUTABLE, arrayOP},
{OB_OPERATOR, XA_EXECUTABLE, endarrayOP},
{OB_OPERATOR, XA_EXECUTABLE, putOP},
{OB_OPERATOR, XA_EXECUTABLE, getOP},
{OB_OPERATOR, XA_EXECUTABLE, putintervalOP},
{OB_OPERATOR, XA_EXECUTABLE, getintervalOP},
{OB_OPERATOR, XA_EXECUTABLE, aloadOP},
{OB_OPERATOR, XA_EXECUTABLE, astoreOP},
{OB_OPERATOR, XA_EXECUTABLE, forallOP},
{OB_OPERATOR, XA_EXECUTABLE, cleartomarkOP},
{OB_OPERATOR, XA_EXECUTABLE, counttomarkOP},
{OB_OPERATOR, XA_EXECUTABLE, equalsequalsOP},
{OB_OPERATOR, XA_EXECUTABLE, defOP},
{OB_OPERATOR, XA_EXECUTABLE, currentdictOP},
{OB_OPERATOR, XA_EXECUTABLE, forOP},
{OB_OPERATOR, XA_EXECUTABLE, repeatOP},
{OB_OPERATOR, XA_EXECUTABLE, loopOP},
{OB_OPERATOR, XA_EXECUTABLE, initgraphicsOP},
{OB_OPERATOR, XA_EXECUTABLE, setlinewidthOP},
{OB_OPERATOR, XA_EXECUTABLE, setmiterlimitOP},
{OB_OPERATOR, XA_EXECUTABLE, setflatOP},
{OB_OPERATOR, XA_EXECUTABLE, setgrayOP},
{OB_OPERATOR, XA_EXECUTABLE, setlinecapOP},
{OB_OPERATOR, XA_EXECUTABLE, setlinejoinOP},
{OB_OPERATOR, XA_EXECUTABLE, setdashOP},
{OB_OPERATOR, XA_EXECUTABLE, currentlinewidthOP},
{OB_OPERATOR, XA_EXECUTABLE, currentmiterlimitOP},
{OB_OPERATOR, XA_EXECUTABLE, currentflatOP},
{OB_OPERATOR, XA_EXECUTABLE, currentgrayOP},
{OB_OPERATOR, XA_EXECUTABLE, currentlinecapOP},
{OB_OPERATOR, XA_EXECUTABLE, currentlinejoinOP},
{OB_OPERATOR, XA_EXECUTABLE, currentdashOP},
{OB_OPERATOR, XA_EXECUTABLE, versionOP},
{OB_OPERATOR, XA_EXECUTABLE, typeOP},
{OB_OPERATOR, XA_EXECUTABLE, cvlitOP},
{OB_OPERATOR, XA_EXECUTABLE, cvxOP},
{OB_OPERATOR, XA_EXECUTABLE, cviOP},
{OB_OPERATOR, XA_EXECUTABLE, cvrOP},
{OB_OPERATOR, XA_EXECUTABLE, cvrsOP},
{OB_OPERATOR, XA_EXECUTABLE, cvnOP},
{OB_OPERATOR, XA_EXECUTABLE, cvsOP},
{OB_OPERATOR, XA_EXECUTABLE, xcheckOP},
{OB_OPERATOR, XA_EXECUTABLE, rcheckOP},
{OB_OPERATOR, XA_EXECUTABLE, wcheckOP},
{OB_OPERATOR, XA_EXECUTABLE, executeonlyOP},
{OB_OPERATOR, XA_EXECUTABLE, readonlyOP},
{OB_OPERATOR, XA_EXECUTABLE, noaccessOP},
{OB_OPERATOR, XA_EXECUTABLE, stringOP},
{OB_OPERATOR, XA_EXECUTABLE, anchorsearchOP},
{OB_OPERATOR, XA_EXECUTABLE, searchOP},
{OB_OPERATOR, XA_EXECUTABLE, tokenOP},
{OB_OPERATOR, XA_EXECUTABLE, matrixOP},
{OB_OPERATOR, XA_EXECUTABLE, identmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, currentmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, setmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, translateOP},
{OB_OPERATOR, XA_EXECUTABLE, scaleOP},
{OB_OPERATOR, XA_EXECUTABLE, rotateOP},
{OB_OPERATOR, XA_EXECUTABLE, concatOP},
{OB_OPERATOR, XA_EXECUTABLE, concatmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, dtransformOP},
{OB_OPERATOR, XA_EXECUTABLE, initmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, defaultmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, invertmatrixOP},
{OB_OPERATOR, XA_EXECUTABLE, itransformOP},
{OB_OPERATOR, XA_EXECUTABLE, idtransformOP},
{OB_OPERATOR, XA_EXECUTABLE, pstackOP},
{OB_OPERATOR, XA_EXECUTABLE, vmstatusOP},
{OB_OPERATOR, XA_EXECUTABLE, fileOP},
{OB_OPERATOR, XA_EXECUTABLE, flushfileOP},
{OB_OPERATOR, XA_EXECUTABLE, closefileOP},
{OB_OPERATOR, XA_EXECUTABLE, readOP},
{OB_OPERATOR, XA_EXECUTABLE, writeOP},
{OB_OPERATOR, XA_EXECUTABLE, readstringOP},
{OB_OPERATOR, XA_EXECUTABLE, readlineOP},
{OB_OPERATOR, XA_EXECUTABLE, writestringOP},
{OB_OPERATOR, XA_EXECUTABLE, bytesavailableOP},
{OB_OPERATOR, XA_EXECUTABLE, statusOP},
{OB_OPERATOR, XA_EXECUTABLE, loadOP},
{OB_OPERATOR, XA_EXECUTABLE, storeOP},
{OB_OPERATOR, XA_EXECUTABLE, whereOP},
{OB_OPERATOR, XA_EXECUTABLE, knownOP},
{OB_OPERATOR, XA_EXECUTABLE, countdictstackOP},
{OB_OPERATOR, XA_EXECUTABLE, dictstackOP},
{OB_OPERATOR, XA_EXECUTABLE, definefontOP},
{OB_OPERATOR, XA_EXECUTABLE, findfontOP},
{OB_OPERATOR, XA_EXECUTABLE, scalefontOP},
{OB_OPERATOR, XA_EXECUTABLE, makefontOP},
{OB_OPERATOR, XA_EXECUTABLE, setfontOP},
{OB_OPERATOR, XA_EXECUTABLE, currentfontOP},
{OB_OPERATOR, XA_EXECUTABLE, execOP},
{OB_OPERATOR, XA_EXECUTABLE, execstackOP},
{OB_OPERATOR, XA_EXECUTABLE, exitOP},
{OB_OPERATOR, XA_EXECUTABLE, quitOP},
{OB_OPERATOR, XA_EXECUTABLE, ifOP},
{OB_OPERATOR, XA_EXECUTABLE, ifelseOP},
{OB_OPERATOR, XA_EXECUTABLE, countexecstackOP},
{OB_OPERATOR, XA_EXECUTABLE, newpathOP},
{OB_OPERATOR, XA_EXECUTABLE, rmovetoOP},
{OB_OPERATOR, XA_EXECUTABLE, linetoOP},
{OB_OPERATOR, XA_EXECUTABLE, rlinetoOP},
{OB_OPERATOR, XA_EXECUTABLE, curvetoOP},
{OB_OPERATOR, XA_EXECUTABLE, rcurvetoOP},
{OB_OPERATOR, XA_EXECUTABLE, closepathOP},
{OB_OPERATOR, XA_EXECUTABLE, pathbboxOP},
{OB_OPERATOR, XA_EXECUTABLE, pathforallOP},
{OB_OPERATOR, XA_EXECUTABLE, flattenpathOP},
{OB_OPERATOR, XA_EXECUTABLE, arcOP},
{OB_OPERATOR, XA_EXECUTABLE, arcnOP},
{OB_OPERATOR, XA_EXECUTABLE, arctoOP},
{OB_OPERATOR, XA_EXECUTABLE, strokeOP},
{OB_OPERATOR, XA_EXECUTABLE, sethsbcolorOP},
{OB_OPERATOR, XA_EXECUTABLE, setrgbcolorOP},
{OB_OPERATOR, XA_EXECUTABLE, currenthsbcolorOP},
{OB_OPERATOR, XA_EXECUTABLE, currentrgbcolorOP},
{OB_OPERATOR, XA_EXECUTABLE, settransferOP},
{OB_OPERATOR, XA_EXECUTABLE, currenttransferOP},
{OB_OPERATOR, XA_EXECUTABLE, usertimeOP},
{OB_OPERATOR, XA_EXECUTABLE, erasepageOP},
{OB_OPERATOR, XA_EXECUTABLE, initclipOP},
{OB_OPERATOR, XA_EXECUTABLE, clippathOP},
{OB_OPERATOR, XA_EXECUTABLE, fillOP},
{OB_OPERATOR, XA_EXECUTABLE, eofillOP},
{OB_OPERATOR, XA_EXECUTABLE, strokepathOP},
{OB_OPERATOR, XA_EXECUTABLE, readhexstringOP},
{OB_OPERATOR, XA_EXECUTABLE, writehexstringOP},
{OB_OPERATOR, XA_EXECUTABLE, stackOP},
{OB_OPERATOR, XA_EXECUTABLE, bindOP},
{OB_OPERATOR, XA_EXECUTABLE, currentfileOP},
{OB_OPERATOR, XA_EXECUTABLE, framedeviceOP},
{OB_OPERATOR, XA_EXECUTABLE, nulldeviceOP},
{OB_OPERATOR, XA_EXECUTABLE, stopOP},
{OB_OPERATOR, XA_EXECUTABLE, stoppedOP},
{OB_OPERATOR, XA_EXECUTABLE, startOP},
{OB_OPERATOR, XA_EXECUTABLE, runOP},
{OB_OPERATOR, XA_EXECUTABLE, setcharwidthOP},
{OB_OPERATOR, XA_EXECUTABLE, stringwidthOP},
{OB_OPERATOR, XA_EXECUTABLE, ashowOP},
{OB_OPERATOR, XA_EXECUTABLE, widthshowOP},
{OB_OPERATOR, XA_EXECUTABLE, awidthshowOP},
{OB_OPERATOR, XA_EXECUTABLE, kshowOP},
{OB_OPERATOR, XA_EXECUTABLE, setscreenOP},
{OB_OPERATOR, XA_EXECUTABLE, currentscreenOP},
{OB_OPERATOR, XA_EXECUTABLE, saveOP},
{OB_OPERATOR, XA_EXECUTABLE, restoreOP},
{OB_OPERATOR, XA_EXECUTABLE, grestoreallOP},
{OB_OPERATOR, XA_EXECUTABLE, countfreeOP},
{OB_OPERATOR, XA_EXECUTABLE, imagemaskOP},
{OB_OPERATOR, XA_EXECUTABLE, imageOP},
{OB_OPERATOR, XA_EXECUTABLE, showpageOP},
{OB_OPERATOR, XA_EXECUTABLE, copypageOP},
{OB_OPERATOR, XA_EXECUTABLE, setcachedeviceOP},
{OB_OPERATOR, XA_EXECUTABLE, clipOP},
{OB_OPERATOR, XA_EXECUTABLE, eoclipOP},
{OB_OPERATOR, XA_EXECUTABLE, charpathOP},
{OB_OPERATOR, XA_EXECUTABLE, cachestatusOP},
/*{OB_OPERATOR, XA_EXECUTABLE, StandardEncodingOP},*/
{OB_OPERATOR, XA_EXECUTABLE, reversepathOP},
{OB_OPERATOR, XA_EXECUTABLE, eexecOP},
{OB_OPERATOR, XA_EXECUTABLE, internaldictOP},
{OB_OPERATOR, XA_EXECUTABLE, letter},
{OB_OPERATOR, XA_EXECUTABLE, legal},
{OB_OPERATOR, XA_EXECUTABLE, debug},
{OB_OPERATOR, XA_EXECUTABLE, printOP},
{OB_OPERATOR, XA_EXECUTABLE, printOP},
{OB_OPERATOR, XA_EXECUTABLE, flushOP},
{OB_OPERATOR, XA_EXECUTABLE, lettertray},
{OB_OPERATOR, XA_EXECUTABLE, outlineOP},
};
struct pstring sproduct = {AC_NONE, 7,(unsigned char *) "Display"};
int Op_nel = NEL(Op_tab);
struct oobject Sop_tab[] = {
{OB_STRING, XA_EXECUTABLE, dummyop},
{OB_OPERATOR, XA_EXECUTABLE, waittimeout},
/*{OB_OPERATOR, XA_EXECUTABLE, letter},*/
{OB_OPERATOR, XA_EXECUTABLE, setjobtimeout},
{OB_OPERATOR, XA_EXECUTABLE, jobname},
{OB_OPERATOR, XA_EXECUTABLE, revision},
{OB_OPERATOR, XA_EXECUTABLE, pagecount},
};
int	Sop_nel = NEL(Sop_tab);
struct pstring Nop_tab[] = {
{AC_NONE, 4, (unsigned char *) "trap"},
{AC_NONE, 4, (unsigned char *) "show"},
{AC_NONE, 6, (unsigned char *) "moveto"},
{AC_NONE, 9, (unsigned char *) "transform"},
{AC_NONE, 5, (unsigned char *) "gsave"},
{AC_NONE, 8, (unsigned char *) "grestore"},
{AC_NONE, 12, (unsigned char *) "currentpoint"},
{AC_NONE, 1, (unsigned char *) "="},
{AC_NONE, 3, (unsigned char *) "abs"},
{AC_NONE, 3, (unsigned char *) "add"},
{AC_NONE, 4, (unsigned char *) "atan"},
{AC_NONE, 7, (unsigned char *) "ceiling"},
{AC_NONE, 3, (unsigned char *) "cos"},
{AC_NONE, 3, (unsigned char *) "div"},
{AC_NONE, 3, (unsigned char *) "exp"},
{AC_NONE, 5, (unsigned char *) "floor"},
{AC_NONE, 4, (unsigned char *) "idiv"},
{AC_NONE, 2, (unsigned char *) "ln"},
{AC_NONE, 3, (unsigned char *) "log"},
{AC_NONE, 3, (unsigned char *) "mod"},
{AC_NONE, 3, (unsigned char *) "mul"},
{AC_NONE, 3, (unsigned char *) "neg"},
{AC_NONE, 4, (unsigned char *) "rand"},
{AC_NONE, 5, (unsigned char *) "round"},
{AC_NONE, 5, (unsigned char *) "rrand"},
{AC_NONE, 3, (unsigned char *) "sin"},
{AC_NONE, 4, (unsigned char *) "sqrt"},
{AC_NONE, 3, (unsigned char *) "sub"},
{AC_NONE, 5, (unsigned char *) "srand"},
{AC_NONE, 8, (unsigned char *) "truncate"},
{AC_NONE, 2, (unsigned char *) "eq"},
{AC_NONE, 2, (unsigned char *) "ne"},
{AC_NONE, 2, (unsigned char *) "ge"},
{AC_NONE, 2, (unsigned char *) "gt"},
{AC_NONE, 2, (unsigned char *) "le"},
{AC_NONE, 2, (unsigned char *) "lt"},
{AC_NONE, 3, (unsigned char *) "and"},
{AC_NONE, 3, (unsigned char *) "not"},
{AC_NONE, 2, (unsigned char *) "or"},
{AC_NONE, 3, (unsigned char *) "xor"},
{AC_NONE, 8, (unsigned char *) "bitshift"},
{AC_NONE, 5, (unsigned char *) "begin"},
{AC_NONE, 3, (unsigned char *) "end"},
{AC_NONE, 4, (unsigned char *) "dict"},
{AC_NONE, 6, (unsigned char *) "length"},
{AC_NONE, 9, (unsigned char *) "maxlength"},
{AC_NONE, 3, (unsigned char *) "pop"},
{AC_NONE, 4, (unsigned char *) "exch"},
{AC_NONE, 3, (unsigned char *) "dup"},
{AC_NONE, 4, (unsigned char *) "copy"},
{AC_NONE, 5, (unsigned char *) "index"},
{AC_NONE, 4, (unsigned char *) "roll"},
{AC_NONE, 5, (unsigned char *) "clear"},
{AC_NONE, 5, (unsigned char *) "count"},
{AC_NONE, 4, (unsigned char *) "mark"},
{AC_NONE, 1, (unsigned char *) "["},
{AC_NONE, 5, (unsigned char *) "array"},
{AC_NONE, 1, (unsigned char *) "]"},
{AC_NONE, 3, (unsigned char *) "put"},
{AC_NONE, 3, (unsigned char *) "get"},
{AC_NONE, 11, (unsigned char *) "putinterval"},
{AC_NONE, 11, (unsigned char *) "getinterval"},
{AC_NONE, 5, (unsigned char *) "aload"},
{AC_NONE, 6, (unsigned char *) "astore"},
{AC_NONE, 6, (unsigned char *) "forall"},
{AC_NONE, 11, (unsigned char *) "cleartomark"},
{AC_NONE, 11, (unsigned char *) "counttomark"},
{AC_NONE, 2, (unsigned char *) "=="},
{AC_NONE, 3, (unsigned char *) "def"},
{AC_NONE, 11, (unsigned char *) "currentdict"},
{AC_NONE, 3, (unsigned char *) "for"},
{AC_NONE, 6, (unsigned char *) "repeat"},
{AC_NONE, 4, (unsigned char *) "loop"},
{AC_NONE, 12, (unsigned char *) "initgraphics"},
{AC_NONE, 12, (unsigned char *) "setlinewidth"},
{AC_NONE, 13, (unsigned char *) "setmiterlimit"},
{AC_NONE, 7, (unsigned char *) "setflat"},
{AC_NONE, 7, (unsigned char *) "setgray"},
{AC_NONE, 10, (unsigned char *) "setlinecap"},
{AC_NONE, 11, (unsigned char *) "setlinejoin"},
{AC_NONE, 7, (unsigned char *) "setdash"},
{AC_NONE, 16, (unsigned char *) "currentlinewidth"},
{AC_NONE, 17, (unsigned char *) "currentmiterlimit"},
{AC_NONE, 11, (unsigned char *) "currentflat"},
{AC_NONE, 11, (unsigned char *) "currentgray"},
{AC_NONE, 14, (unsigned char *) "currentlinecap"},
{AC_NONE, 15, (unsigned char *) "currentlinejoin"},
{AC_NONE, 11, (unsigned char *) "currentdash"},
{AC_NONE, 7, (unsigned char *) "version"},
{AC_NONE, 4, (unsigned char *) "type"},
{AC_NONE, 5, (unsigned char *) "cvlit"},
{AC_NONE, 3, (unsigned char *) "cvx"},
{AC_NONE, 3, (unsigned char *) "cvi"},
{AC_NONE, 3, (unsigned char *) "cvr"},
{AC_NONE, 4, (unsigned char *) "cvrs"},
{AC_NONE, 3, (unsigned char *) "cvn"},
{AC_NONE, 3, (unsigned char *) "cvs"},
{AC_NONE, 6, (unsigned char *) "xcheck"},
{AC_NONE, 6, (unsigned char *) "rcheck"},
{AC_NONE, 6, (unsigned char *) "wcheck"},
{AC_NONE, 11, (unsigned char *) "executeonly"},
{AC_NONE, 8, (unsigned char *) "readonly"},
{AC_NONE, 8, (unsigned char *) "noaccess"},
{AC_NONE, 6, (unsigned char *) "string"},
{AC_NONE, 12, (unsigned char *) "anchorsearch"},
{AC_NONE, 6, (unsigned char *) "search"},
{AC_NONE, 5, (unsigned char *) "token"},
{AC_NONE, 6, (unsigned char *) "matrix"},
{AC_NONE, 11, (unsigned char *) "identmatrix"},
{AC_NONE, 13, (unsigned char *) "currentmatrix"},
{AC_NONE, 9, (unsigned char *) "setmatrix"},
{AC_NONE, 9, (unsigned char *) "translate"},
{AC_NONE, 5, (unsigned char *) "scale"},
{AC_NONE, 6, (unsigned char *) "rotate"},
{AC_NONE, 6, (unsigned char *) "concat"},
{AC_NONE, 12, (unsigned char *) "concatmatrix"},
{AC_NONE, 10, (unsigned char *) "dtransform"},
{AC_NONE, 10, (unsigned char *) "initmatrix"},
{AC_NONE, 13, (unsigned char *) "defaultmatrix"},
{AC_NONE, 12, (unsigned char *) "invertmatrix"},
{AC_NONE, 10, (unsigned char *) "itransform"},
{AC_NONE, 11, (unsigned char *) "idtransform"},
{AC_NONE, 6, (unsigned char *) "pstack"},
{AC_NONE, 8, (unsigned char *) "vmstatus"},
{AC_NONE, 4, (unsigned char *) "file"},
{AC_NONE, 9, (unsigned char *) "flushfile"},
{AC_NONE, 9, (unsigned char *) "closefile"},
{AC_NONE, 4, (unsigned char *) "read"},
{AC_NONE, 5, (unsigned char *) "write"},
{AC_NONE, 10, (unsigned char *) "readstring"},
{AC_NONE, 8, (unsigned char *) "readline"},
{AC_NONE, 11, (unsigned char *) "writestring"},
{AC_NONE, 14, (unsigned char *) "bytesavailable"},
{AC_NONE, 6, (unsigned char *) "status"},
{AC_NONE, 4, (unsigned char *) "load"},
{AC_NONE, 5, (unsigned char *) "store"},
{AC_NONE, 5, (unsigned char *) "where"},
{AC_NONE, 5, (unsigned char *) "known"},
{AC_NONE, 14, (unsigned char *) "countdictstack"},
{AC_NONE, 9, (unsigned char *) "dictstack"},
{AC_NONE, 10, (unsigned char *) "definefont"},
{AC_NONE, 8, (unsigned char *) "findfont"},
{AC_NONE, 9, (unsigned char *) "scalefont"},
{AC_NONE, 8, (unsigned char *) "makefont"},
{AC_NONE, 7, (unsigned char *) "setfont"},
{AC_NONE, 11, (unsigned char *) "currentfont"},
{AC_NONE, 4, (unsigned char *) "exec"},
{AC_NONE, 9, (unsigned char *) "execstack"},
{AC_NONE, 4, (unsigned char *) "exit"},
{AC_NONE, 4, (unsigned char *) "quit"},
{AC_NONE, 2, (unsigned char *) "if"},
{AC_NONE, 6, (unsigned char *) "ifelse"},
{AC_NONE, 14, (unsigned char *) "countexecstack"},
{AC_NONE, 7, (unsigned char *) "newpath"},
{AC_NONE, 7, (unsigned char *) "rmoveto"},
{AC_NONE, 6, (unsigned char *) "lineto"},
{AC_NONE, 7, (unsigned char *) "rlineto"},
{AC_NONE, 7, (unsigned char *) "curveto"},
{AC_NONE, 8, (unsigned char *) "rcurveto"},
{AC_NONE, 9, (unsigned char *) "closepath"},
{AC_NONE, 8, (unsigned char *) "pathbbox"},
{AC_NONE, 10, (unsigned char *) "pathforall"},
{AC_NONE, 11, (unsigned char *) "flattenpath"},
{AC_NONE, 3, (unsigned char *) "arc"},
{AC_NONE, 4, (unsigned char *) "arcn"},
{AC_NONE, 5, (unsigned char *) "arcto"},
{AC_NONE, 6, (unsigned char *) "stroke"},
{AC_NONE, 11, (unsigned char *) "sethsbcolor"},
{AC_NONE, 11, (unsigned char *) "setrgbcolor"},
{AC_NONE, 15, (unsigned char *) "currenthsbcolor"},
{AC_NONE, 15, (unsigned char *) "currentrgbcolor"},
{AC_NONE, 11, (unsigned char *) "settransfer"},
{AC_NONE, 15, (unsigned char *) "currenttransfer"},
{AC_NONE, 8, (unsigned char *) "usertime"},
{AC_NONE, 9, (unsigned char *) "erasepage"},
{AC_NONE, 8, (unsigned char *) "initclip"},
{AC_NONE, 8, (unsigned char *) "clippath"},
{AC_NONE, 4, (unsigned char *) "fill"},
{AC_NONE, 6, (unsigned char *) "eofill"},
{AC_NONE, 10, (unsigned char *) "strokepath"},
{AC_NONE, 13, (unsigned char *) "readhexstring"},
{AC_NONE, 14, (unsigned char *) "writehexstring"},
{AC_NONE, 5, (unsigned char *) "stack"},
{AC_NONE, 4, (unsigned char *) "bind"},
{AC_NONE, 11, (unsigned char *) "currentfile"},
{AC_NONE, 11, (unsigned char *) "framedevice"},
{AC_NONE, 10, (unsigned char *) "nulldevice"},
{AC_NONE, 4, (unsigned char *) "stop"},
{AC_NONE, 7, (unsigned char *) "stopped"},
{AC_NONE, 5, (unsigned char *) "start"},
{AC_NONE, 3, (unsigned char *) "run"},
{AC_NONE, 12, (unsigned char *) "setcharwidth"},
{AC_NONE, 11, (unsigned char *) "stringwidth"},
{AC_NONE, 5, (unsigned char *) "ashow"},
{AC_NONE, 9, (unsigned char *) "widthshow"},
{AC_NONE, 10, (unsigned char *) "awidthshow"},
{AC_NONE, 5, (unsigned char *) "kshow"},
{AC_NONE, 9, (unsigned char *) "setscreen"},
{AC_NONE, 13, (unsigned char *) "currentscreen"},
{AC_NONE, 4, (unsigned char *) "save"},
{AC_NONE, 7, (unsigned char *) "restore"},
{AC_NONE, 11, (unsigned char *) "grestoreall"},
{AC_NONE, 9, (unsigned char *) "countfree"},
{AC_NONE, 9, (unsigned char *) "imagemask"},
{AC_NONE, 5, (unsigned char *) "image"},
{AC_NONE, 8, (unsigned char *) "showpage"},
{AC_NONE, 8, (unsigned char *) "copypage"},
{AC_NONE, 14, (unsigned char *) "setcachedevice"},
{AC_NONE, 4, (unsigned char *) "clip"},
{AC_NONE, 6, (unsigned char *) "eoclip"},
{AC_NONE, 8, (unsigned char *) "charpath"},
{AC_NONE, 11, (unsigned char *) "cachestatus"},
/*{AC_NONE, 16, (unsigned char *) "StandardEncoding"},*/
{AC_NONE, 11, (unsigned char *) "reversepath"},
{AC_NONE, 5, (unsigned char *) "eexec"},
{AC_NONE, 12, (unsigned char *) "internaldict"},
{AC_NONE, 6, (unsigned char *) "letter"},
{AC_NONE, 5, (unsigned char *) "legal"},
{AC_NONE, 5, (unsigned char *) "debug"},
{AC_NONE, 6, (unsigned char *) "=print"},
{AC_NONE, 5, (unsigned char *) "print"},
{AC_NONE, 5, (unsigned char *) "flush"},
{AC_NONE, 10, (unsigned char *) "lettertray"},
{AC_NONE, 7, (unsigned char *) "outline"},
};
int nNop_nel = NEL(Nop_tab);
struct pstring NSop_tab[] = {
{AC_NONE, 7, (unsigned char *) "product"},			/*leave this here*/
{AC_NONE, 11, (unsigned char *) "waittimeout"},
/*{AC_NONE, 6, (unsigned char *) "letter"},*/
{AC_NONE, 13, (unsigned char *) "setjobtimeout"},
{AC_NONE, 7, (unsigned char *) "jobname"},
{AC_NONE, 8, (unsigned char *) "revision"},
{AC_NONE, 9, (unsigned char *) "pagecount"},
};
int nSop_nel = NEL(NSop_tab);
