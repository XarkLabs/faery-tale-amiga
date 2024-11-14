#ifndef  CLIB_LOWLEVEL_PROTOS_H
#define  CLIB_LOWLEVEL_PROTOS_H

/*
**	$VER: lowlevel_protos.h 40.6 (30.7.93)
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
#ifndef  EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif
#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef  DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef  LIBRARIES_LOWLEVEL_H
#include <libraries/lowlevel.h>
#endif
/*--- functions in V40 or higher (Release 3.1) ---*/

/* CONTROLLER HANDLING */

ULONG ReadJoyPort( unsigned long port );

/* LANGUAGE HANDLING */

UBYTE GetLanguageSelection( void );

/* KEYBOARD HANDLING */

ULONG GetKey( void );
void QueryKeys( struct KeyQuery *queryArray, unsigned long arraySize );
APTR AddKBInt( APTR intRoutine, APTR intData );
void RemKBInt( APTR intHandle );

/* SYSTEM HANDLING */

ULONG SystemControlA( struct TagItem *tagList );
ULONG SystemControl( Tag firstTag, ... );

/* TIMER HANDLING */

APTR AddTimerInt( APTR intRoutine, APTR intData );
void RemTimerInt( APTR intHandle );
void StopTimerInt( APTR intHandle );
void StartTimerInt( APTR intHandle, unsigned long timeInterval,
	long continuous );
ULONG ElapsedTime( struct EClockVal *context );

/* VBLANK HANDLING */

APTR AddVBlankInt( APTR intRoutine, APTR intData );
void RemVBlankInt( APTR intHandle );

/* MORE CONTROLLER HANDLING */

BOOL SetJoyPortAttrsA( unsigned long portNumber, struct TagItem *tagList );
BOOL SetJoyPortAttrs( unsigned long portNumber, Tag firstTag, ... );
#endif	 /* CLIB_LOWLEVEL_PROTOS_H */
