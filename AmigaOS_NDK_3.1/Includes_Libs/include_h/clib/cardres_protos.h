#ifndef  CLIB_CARDRES_PROTOS_H
#define  CLIB_CARDRES_PROTOS_H

/*
**	$VER: cardres_protos.h 1.2 (8.9.92)
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
#ifndef  EXEC_RESIDENT_H
#include <exec/resident.h>
#endif
#ifndef  RESOURCES_CARD_H
#include <resources/card.h>
#endif
struct CardHandle *OwnCard( struct CardHandle *handle );
void ReleaseCard( struct CardHandle *handle, uint32_t flags );
struct CardMemoryMap *GetCardMap( void );
BOOL BeginCardAccess( struct CardHandle *handle );
BOOL EndCardAccess( struct CardHandle *handle );
UBYTE ReadCardStatus( void );
BOOL CardResetRemove( struct CardHandle *handle, uint32_t flag );
UBYTE CardMiscControl( struct CardHandle *handle,
	uint32_t control_bits );
ULONG CardAccessSpeed( struct CardHandle *handle, uint32_t nanoseconds );
LONG CardProgramVoltage( struct CardHandle *handle, uint32_t voltage );
BOOL CardResetCard( struct CardHandle *handle );
BOOL CopyTuple( struct CardHandle *handle, UBYTE *buffer,
	uint32_t tuplecode, uint32_t size );
ULONG DeviceTuple( UBYTE *tuple_data, struct DeviceTData *storage );
struct Resident *IfAmigaXIP( struct CardHandle *handle );
BOOL CardForceChange( void );
ULONG CardChangeCount( void );
ULONG CardInterface( void );
#endif	 /* CLIB_CARDRES_PROTOS_H */
