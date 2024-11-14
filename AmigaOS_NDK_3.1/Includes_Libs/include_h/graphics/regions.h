#ifndef	GRAPHICS_REGIONS_H
#define	GRAPHICS_REGIONS_H
/*
**	$VER: regions.h 39.0 (21.8.91)
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

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

struct RegionRectangle
{
    struct RegionRectangle *Next,*Prev;
    struct Rectangle bounds;
};

struct Region
{
    struct Rectangle bounds;
    struct RegionRectangle *RegionRectangle;
};

#endif	/* GRAPHICS_REGIONS_H */
