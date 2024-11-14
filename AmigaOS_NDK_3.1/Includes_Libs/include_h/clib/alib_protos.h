#ifndef  CLIB_ALIB_PROTOS_H
#define  CLIB_ALIB_PROTOS_H

/*
**	$VER: alib_protos.h 1.5 (25.8.92)
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
#ifndef  DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef  DEVICES_KEYMAP_H
#include <devices/keymap.h>
#endif
#ifndef  LIBRARIES_COMMODITIES_H
#include <libraries/commodities.h>
#endif
#ifndef  UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef  INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef  INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif
#ifndef  GRAPHICS_GRAPHINT_H
#include <graphics/graphint.h>
#endif

/*  Exec support functions */

void BeginIO( struct IORequest *ioReq );
struct IORequest *CreateExtIO( struct MsgPort *port, int32_t ioSize );
struct MsgPort *CreatePort( STRPTR name, int32_t pri );
struct IOStdReq *CreateStdIO( struct MsgPort *port );
struct Task *CreateTask( STRPTR name, int32_t pri, APTR initPC,
	uint32_t stackSize );
void DeleteExtIO( struct IORequest *ioReq );
void DeletePort( struct MsgPort *ioReq );
void DeleteStdIO( struct IOStdReq *ioReq );
void DeleteTask( struct Task *task );
void NewList( struct List *list );
APTR LibAllocPooled( APTR poolHeader, uint32_t memSize );
APTR LibCreatePool( uint32_t memFlags, uint32_t puddleSize,
	uint32_t threshSize );
void LibDeletePool( APTR poolHeader );
void LibFreePooled( APTR poolHeader, APTR memory, uint32_t memSize );

/* Assorted functions in amiga.lib */

ULONG FastRand( uint32_t seed );
UWORD RangeRand( uint32_t maxValue );

/* Graphics support functions in amiga.lib */

void AddTOF( struct Isrvstr *i, int32_t (*p)(), int32_t a );
void RemTOF( struct Isrvstr *i );
void waitbeam( int32_t b );

/* math support functions in amiga.lib */

FLOAT afp( BYTE *string );
void arnd( int32_t place, int32_t exp, BYTE *string );
FLOAT dbf( uint32_t exp, uint32_t mant );
LONG fpa( FLOAT fnum, BYTE *string );
void fpbcd( FLOAT fnum, BYTE *string );

/* Timer support functions in amiga.lib (V36 and higher only) */

LONG TimeDelay( int32_t unit, uint32_t secs, uint32_t microsecs );
LONG DoTimer( struct timeval *, int32_t unit, int32_t command );

/*  Commodities functions in amiga.lib (V36 and higher only) */

void ArgArrayDone( void );
UBYTE **ArgArrayInit( int32_t argc, UBYTE **argv );
LONG ArgInt( UBYTE **tt, STRPTR entry, int32_t defaultval );
STRPTR ArgString( UBYTE **tt, STRPTR entry, STRPTR defaulstring );
CxObj *HotKey( STRPTR description, struct MsgPort *port, int32_t id );
struct InputEvent *InvertString( STRPTR str, struct KeyMap *km );
void FreeIEvents( struct InputEvent *events );

/* Commodities Macros */

/* CxObj *CxCustom(LONG(*)(),LONG id)(A0,D0) */
/* CxObj *CxDebug(LONG id)(D0) */
/* CxObj *CxFilter(STRPTR description)(A0) */
/* CxObj *CxSender(struct MsgPort *port,LONG id)(A0,D0) */
/* CxObj *CxSignal(struct Task *task,LONG signal)(A0,D0) */
/* CxObj *CxTranslate(struct InputEvent *ie)(A0) */

/*  ARexx support functions in amiga.lib */

BOOL CheckRexxMsg( struct Message *rexxmsg );
LONG GetRexxVar( struct Message *rexxmsg, UBYTE *name, UBYTE **result );
LONG SetRexxVar( struct Message *rexxmsg, UBYTE *name, UBYTE *value,
	int32_t length );

/*  Intuition hook and boopsi support functions in amiga.lib. */
/*  These functions do not require any particular ROM revision */
/*  to operate correctly, though they deal with concepts first introduced */
/*  in V36.  These functions would work with compatibly-implemented */
/*  hooks or objects under V34. */

ULONG CallHookA( struct Hook *hookPtr, Object *obj, APTR message );
ULONG CallHook( struct Hook *hookPtr, Object *obj, ... );
ULONG DoMethodA( Object *obj, Msg message );
ULONG DoMethod( Object *obj, uint32_t MethodID, ... );
ULONG DoSuperMethodA( struct IClass *cl, Object *obj, Msg message );
ULONG DoSuperMethod( struct IClass *cl, Object *obj, uint32_t MethodID,
	... );
ULONG CoerceMethodA( struct IClass *cl, Object *obj, Msg message );
ULONG CoerceMethod( struct IClass *cl, Object *obj, uint32_t MethodID,
	... );
ULONG SetSuperAttrs( struct IClass *cl, Object *obj, uint32_t Tag1,
	... );

/*  Network-support functions in amiga.lib. */
/*  ACrypt() first appeared in later V39 versions of amiga.lib, but */
/*  operates correctly under V37 and up. */

STRPTR ACrypt( STRPTR buffer, STRPTR password, STRPTR username );
#endif	 /* CLIB_ALIB_PROTOS_H */
