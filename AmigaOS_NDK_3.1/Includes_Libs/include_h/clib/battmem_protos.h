#ifndef  CLIB_BATTMEM_PROTOS_H
#define  CLIB_BATTMEM_PROTOS_H

/*
**	$VER: battmem_protos.h 1.5 (4.3.91)
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
void ObtainBattSemaphore( void );
void ReleaseBattSemaphore( void );
ULONG ReadBattMem( APTR buffer, unsigned long offset, unsigned long length );
ULONG WriteBattMem( APTR buffer, unsigned long offset, unsigned long length );
#endif	 /* CLIB_BATTMEM_PROTOS_H */
