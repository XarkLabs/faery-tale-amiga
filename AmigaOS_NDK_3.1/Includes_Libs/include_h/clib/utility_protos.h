#ifndef  CLIB_UTILITY_PROTOS_H
#define  CLIB_UTILITY_PROTOS_H

/*
**	$VER: utility_protos.h 39.12 (10.2.93)
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
#ifndef  EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef  UTILITY_DATE_H
#include <utility/date.h>
#endif
#ifndef  UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef  UTILITY_NAME_H
#include <utility/name.h>
#endif
/*--- functions in V36 or higher (Release 2.0) ---*/

/* Tag item functions */

struct TagItem *FindTagItem( Tag tagVal, struct TagItem *tagList );
ULONG GetTagData( Tag tagValue, uint32_t defaultVal,
	struct TagItem *tagList );
ULONG PackBoolTags( uint32_t initialFlags, struct TagItem *tagList,
	struct TagItem *boolMap );
struct TagItem *NextTagItem( struct TagItem **tagListPtr );
void FilterTagChanges( struct TagItem *changeList,
	struct TagItem *originalList, uint32_t apply );
void MapTags( struct TagItem *tagList, struct TagItem *mapList,
	uint32_t mapType );
struct TagItem *AllocateTagItems( uint32_t numTags );
struct TagItem *CloneTagItems( struct TagItem *tagList );
void FreeTagItems( struct TagItem *tagList );
void RefreshTagItemClones( struct TagItem *clone, struct TagItem *original );
BOOL TagInArray( Tag tagValue, Tag *tagArray );
ULONG FilterTagItems( struct TagItem *tagList, Tag *filterArray,
	uint32_t logic );

/* Hook functions */

ULONG CallHookPkt( struct Hook *hook, APTR object, APTR paramPacket );

/* Date functions */

void Amiga2Date( uint32_t seconds, struct ClockData *result );
ULONG Date2Amiga( struct ClockData *date );
ULONG CheckDate( struct ClockData *date );

/* 32 bit integer muliply functions */

LONG SMult32( int32_t arg1, int32_t arg2 );
ULONG UMult32( uint32_t arg1, uint32_t arg2 );

/* 32 bit integer division funtions. The quotient and the remainder are */
/* returned respectively in d0 and d1 */

LONG SDivMod32( int32_t dividend, int32_t divisor );
ULONG UDivMod32( uint32_t dividend, uint32_t divisor );
/*--- functions in V37 or higher (Release 2.04) ---*/

/* International string routines */

LONG Stricmp( STRPTR string1, STRPTR string2 );
LONG Strnicmp( STRPTR string1, STRPTR string2, int32_t length );
UBYTE ToUpper( uint32_t character );
UBYTE ToLower( uint32_t character );
/*--- functions in V39 or higher (Release 3) ---*/

/* More tag Item functions */

void ApplyTagChanges( struct TagItem *list, struct TagItem *changeList );

/* 64 bit integer muliply functions. The results are 64 bit quantities */
/* returned in D0 and D1 */

LONG SMult64( int32_t arg1, int32_t arg2 );
ULONG UMult64( uint32_t arg1, uint32_t arg2 );

/* Structure to Tag and Tag to Structure support routines */

ULONG PackStructureTags( APTR pack, ULONG *packTable,
	struct TagItem *tagList );
ULONG UnpackStructureTags( APTR pack, ULONG *packTable,
	struct TagItem *tagList );

/* New, object-oriented NameSpaces */

BOOL AddNamedObject( struct NamedObject *nameSpace,
	struct NamedObject *object );
struct NamedObject *AllocNamedObjectA( STRPTR name, struct TagItem *tagList );
struct NamedObject *AllocNamedObject( STRPTR name, Tag tag1, ... );
LONG AttemptRemNamedObject( struct NamedObject *object );
struct NamedObject *FindNamedObject( struct NamedObject *nameSpace,
	STRPTR name, struct NamedObject *lastObject );
void FreeNamedObject( struct NamedObject *object );
STRPTR NamedObjectName( struct NamedObject *object );
void ReleaseNamedObject( struct NamedObject *object );
void RemNamedObject( struct NamedObject *object, struct Message *message );

/* Unique ID generator */

ULONG GetUniqueID( void );


#endif	 /* CLIB_UTILITY_PROTOS_H */
