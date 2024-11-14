#ifndef	GRAPHICS_GFXMACROS_H
#define	GRAPHICS_GFXMACROS_H
/*
**	$VER: gfxmacros.h 39.3 (31.5.93)
**	Includes Release 40.15
**
**
**
**	(C) Copyright 1985-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef  GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif

#define ON_DISPLAY	custom.dmacon = BITSET|DMAF_RASTER;
#define OFF_DISPLAY	custom.dmacon = BITCLR|DMAF_RASTER;
#define ON_SPRITE	custom.dmacon = BITSET|DMAF_SPRITE;
#define OFF_SPRITE	custom.dmacon = BITCLR|DMAF_SPRITE;

#define ON_VBLANK	custom.intena = BITSET|INTF_VERTB;
#define OFF_VBLANK	custom.intena = BITCLR|INTF_VERTB;

#define SetDrPt(w,p)	{(w)->LinePtrn = p;(w)->Flags |= FRST_DOT;(w)->linpatcnt=15;}
#define SetAfPt(w,p,n)	{(w)->AreaPtrn = p;(w)->AreaPtSz = n;}

#define SetOPen(w,c)	{(w)->AOlPen = c;(w)->Flags |= AREAOUTLINE;}
#define SetWrMsk(w,m)	{(w)->Mask = m;}

/* the SafeSetxxx macros are backwards (pre V39 graphics) compatible versions */
/* using these macros will make your code do the right thing under V39 AND V37 */
#define SafeSetOutlinePen(w,c)	  {if (GfxBase->LibNode.lib_Version<39) { (w)->AOlPen = c;(w)->Flags |= AREAOUTLINE;} else SetOutlinePen(w,c); }
#define SafeSetWriteMask(w,m)	{if (GfxBase->LibNode.lib_Version<39) { (w)->Mask = (m);} else SetWriteMask(w,m); }

/* synonym for GetOPen for consistency with SetOutlinePen */
#define GetOutlinePen(rp) GetOPen(rp)

#define BNDRYOFF(w)	{(w)->Flags &= ~AREAOUTLINE;}

#define CINIT(c,n)	  UCopperListInit(c,n);
#define CMOVE(c,a,b)	{ CMove(c,&a,b);CBump(c); }
#define CWAIT(c,a,b)	{ CWait(c,a,b);CBump(c); }
#define CEND(c)	{ CWAIT(c,10000,255); }

#define DrawCircle(rp,cx,cy,r)	DrawEllipse(rp,cx,cy,r,r);
#define AreaCircle(rp,cx,cy,r)	AreaEllipse(rp,cx,cy,r,r);

#endif	/* GRAPHICS_GFXMACROS_H */
