#ifndef  CLIB_POTGO_PROTOS_H
#define  CLIB_POTGO_PROTOS_H

/*
**	$VER: potgo_protos.h 36.3 (7.11.90)
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
UWORD AllocPotBits( uint32_t bits );
void FreePotBits( uint32_t bits );
void WritePotgo( uint32_t word, uint32_t mask );
#endif	 /* CLIB_POTGO_PROTOS_H */
