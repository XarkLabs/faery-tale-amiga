#ifndef  CLIB_ALIB_STDIO_PROTOS_H
#define  CLIB_ALIB_STDIO_PROTOS_H

/*
**	$VER: alib_stdio_protos.h 39.1 (25.8.92)
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

/* stdio functions that duplicate those in a typical C library */

LONG printf( STRPTR fmt, ... );
LONG sprintf( STRPTR buffer, STRPTR fmt, ... );
LONG fclose( int32_t stream );
LONG fgetc( int32_t stream );
LONG fprintf( int32_t stream, STRPTR fmt, ... );
LONG fputc( int32_t c, int32_t stream );
LONG fputs( UBYTE *s, int32_t stream );
LONG getchar( void );
LONG putchar( int32_t c );
LONG puts( BYTE *s );
#endif	 /* CLIB_ALIB_STDIO_PROTOS_H */
