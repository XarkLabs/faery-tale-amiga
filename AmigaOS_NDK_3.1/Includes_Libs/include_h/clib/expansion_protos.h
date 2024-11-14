#ifndef  CLIB_EXPANSION_PROTOS_H
#define  CLIB_EXPANSION_PROTOS_H

/*
**	$VER: expansion_protos.h 39.0 (31.10.91)
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
/*--- functions in V33 or higher (Release 1.2) ---*/
void AddConfigDev( struct ConfigDev *configDev );
/*--- functions in V36 or higher (Release 2.0) ---*/
BOOL AddBootNode( int32_t bootPri, uint32_t flags,
	struct DeviceNode *deviceNode, struct ConfigDev *configDev );
/*--- functions in V33 or higher (Release 1.2) ---*/
void AllocBoardMem( uint32_t slotSpec );
struct ConfigDev *AllocConfigDev( void );
APTR AllocExpansionMem( uint32_t numSlots, uint32_t slotAlign );
void ConfigBoard( APTR board, struct ConfigDev *configDev );
void ConfigChain( APTR baseAddr );
struct ConfigDev *FindConfigDev( struct ConfigDev *oldConfigDev,
	int32_t manufacturer, int32_t product );
void FreeBoardMem( uint32_t startSlot, uint32_t slotSpec );
void FreeConfigDev( struct ConfigDev *configDev );
void FreeExpansionMem( uint32_t startSlot, uint32_t numSlots );
UBYTE ReadExpansionByte( APTR board, uint32_t offset );
void ReadExpansionRom( APTR board, struct ConfigDev *configDev );
void RemConfigDev( struct ConfigDev *configDev );
void WriteExpansionByte( APTR board, uint32_t offset,
	uint32_t byte );
void ObtainConfigBinding( void );
void ReleaseConfigBinding( void );
void SetCurrentBinding( struct CurrentBinding *currentBinding,
	uint32_t bindingSize );
ULONG GetCurrentBinding( struct CurrentBinding *currentBinding,
	uint32_t bindingSize );
struct DeviceNode *MakeDosNode( APTR parmPacket );
BOOL AddDosNode( int32_t bootPri, uint32_t flags,
	struct DeviceNode *deviceNode );
/*--- functions in V36 or higher (Release 2.0) ---*/
#endif	 /* CLIB_EXPANSION_PROTOS_H */
