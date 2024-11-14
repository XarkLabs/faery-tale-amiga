#ifndef  CLIB_REXXSYSLIB_PROTOS_H
#define  CLIB_REXXSYSLIB_PROTOS_H

/*
**	$VER: rexxsyslib_protos.h 36.3 (19.2.91)
**	Includes Release 40.15
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 1990-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

/*--- functions in V33 or higher (Release 1.2) ---*/
#ifndef  EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef  REXX_RXSLIB_H
#include <rexx/rxslib.h>
#endif
#ifndef  REXX_REXXIO_H
#include <rexx/rexxio.h>
#endif

UBYTE *CreateArgstring( UBYTE *string, uint32_t length );
void DeleteArgstring( UBYTE *argstring );
ULONG LengthArgstring( UBYTE *argstring );
struct RexxMsg *CreateRexxMsg( struct MsgPort *port, UBYTE *extension,
	UBYTE *host );
void DeleteRexxMsg( struct RexxMsg *packet );
void ClearRexxMsg( struct RexxMsg *msgptr, uint32_t count );
BOOL FillRexxMsg( struct RexxMsg *msgptr, uint32_t count,
	uint32_t mask );
BOOL IsRexxMsg( struct RexxMsg *msgptr );


void LockRexxBase( uint32_t resource );
void UnlockRexxBase( uint32_t resource );

#endif	 /* CLIB_REXXSYSLIB_PROTOS_H */
