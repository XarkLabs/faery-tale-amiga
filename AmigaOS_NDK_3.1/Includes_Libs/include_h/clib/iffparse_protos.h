#ifndef  CLIB_IFFPARSE_PROTOS_H
#define  CLIB_IFFPARSE_PROTOS_H

/*
**	$VER: iffparse_protos.h 39.1 (1.6.92)
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
#ifndef  LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif
/*--- functions in V36 or higher (Release 2.0) ---*/

/* Basic functions */

struct IFFHandle *AllocIFF( void );
LONG OpenIFF( struct IFFHandle *iff, int32_t rwMode );
LONG ParseIFF( struct IFFHandle *iff, int32_t control );
void CloseIFF( struct IFFHandle *iff );
void FreeIFF( struct IFFHandle *iff );

/* Read/Write functions */

LONG ReadChunkBytes( struct IFFHandle *iff, APTR buf, int32_t numBytes );
LONG WriteChunkBytes( struct IFFHandle *iff, APTR buf, int32_t numBytes );
LONG ReadChunkRecords( struct IFFHandle *iff, APTR buf, int32_t bytesPerRecord,
	int32_t numRecords );
LONG WriteChunkRecords( struct IFFHandle *iff, APTR buf, int32_t bytesPerRecord,
	int32_t numRecords );

/* Context entry/exit */

LONG PushChunk( struct IFFHandle *iff, int32_t type, int32_t id, int32_t size );
LONG PopChunk( struct IFFHandle *iff );

/* Low-level handler installation */

LONG EntryHandler( struct IFFHandle *iff, int32_t type, int32_t id, int32_t position,
	struct Hook *handler, APTR object );
LONG ExitHandler( struct IFFHandle *iff, int32_t type, int32_t id, int32_t position,
	struct Hook *handler, APTR object );

/* Built-in chunk/property handlers */

LONG PropChunk( struct IFFHandle *iff, int32_t type, int32_t id );
LONG PropChunks( struct IFFHandle *iff, LONG *propArray, int32_t numPairs );
LONG StopChunk( struct IFFHandle *iff, int32_t type, int32_t id );
LONG StopChunks( struct IFFHandle *iff, LONG *propArray, int32_t numPairs );
LONG CollectionChunk( struct IFFHandle *iff, int32_t type, int32_t id );
LONG CollectionChunks( struct IFFHandle *iff, LONG *propArray,
	int32_t numPairs );
LONG StopOnExit( struct IFFHandle *iff, int32_t type, int32_t id );

/* Context utilities */

struct StoredProperty *FindProp( struct IFFHandle *iff, int32_t type, int32_t id );
struct CollectionItem *FindCollection( struct IFFHandle *iff, int32_t type,
	int32_t id );
struct ContextNode *FindPropContext( struct IFFHandle *iff );
struct ContextNode *CurrentChunk( struct IFFHandle *iff );
struct ContextNode *ParentChunk( struct ContextNode *contextNode );

/* LocalContextItem support functions */

struct LocalContextItem *AllocLocalItem( int32_t type, int32_t id, int32_t ident,
	int32_t dataSize );
APTR LocalItemData( struct LocalContextItem *localItem );
void SetLocalItemPurge( struct LocalContextItem *localItem,
	struct Hook *purgeHook );
void FreeLocalItem( struct LocalContextItem *localItem );
struct LocalContextItem *FindLocalItem( struct IFFHandle *iff, int32_t type,
	int32_t id, int32_t ident );
LONG StoreLocalItem( struct IFFHandle *iff, struct LocalContextItem *localItem,
	int32_t position );
void StoreItemInContext( struct IFFHandle *iff,
	struct LocalContextItem *localItem,
	struct ContextNode *contextNode );

/* IFFHandle initialization */

void InitIFF( struct IFFHandle *iff, int32_t flags, struct Hook *streamHook );
void InitIFFasDOS( struct IFFHandle *iff );
void InitIFFasClip( struct IFFHandle *iff );

/* Internal clipboard support */

struct ClipboardHandle *OpenClipboard( int32_t unitNumber );
void CloseClipboard( struct ClipboardHandle *clipHandle );

/* Miscellaneous */

LONG GoodID( int32_t id );
LONG GoodType( int32_t type );
STRPTR IDtoStr( int32_t id, STRPTR buf );
#endif	 /* CLIB_IFFPARSE_PROTOS_H */
