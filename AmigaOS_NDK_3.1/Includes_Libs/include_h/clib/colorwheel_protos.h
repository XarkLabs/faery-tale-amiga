#ifndef  CLIB_COLORWHEEL_PROTOS_H
#define  CLIB_COLORWHEEL_PROTOS_H

/*
**	$VER: colorwheel_protos.h 39.1 (21.7.92)
**	Includes Release 40.15
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 1990-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef  EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef  GADGETS_COLORWHEEL_H
#include <gadgets/colorwheel.h>
#endif
/*--- functions in V39 or higher (Release 3) ---*/

/* Public entries */

void ConvertHSBToRGB( struct ColorWheelHSB *hsb, struct ColorWheelRGB *rgb );
void ConvertRGBToHSB( struct ColorWheelRGB *rgb, struct ColorWheelHSB *hsb );
#endif	 /* CLIB_COLORWHEEL_PROTOS_H */
