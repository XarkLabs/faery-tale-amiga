#ifndef  CLIB_LOCALE_PROTOS_H
#define  CLIB_LOCALE_PROTOS_H

/*
**	$VER: locale_protos.h 38.5 (18.6.93)
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
#ifndef  LIBRARIES_LOCALE_H
#include <libraries/locale.h>
#endif
#ifndef  DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef  UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef  REXX_STORAGE_H
#include <rexx/storage.h>
#endif
/*--- functions in V38 or higher (Release 2.1) ---*/
void CloseCatalog( struct Catalog *catalog );
void CloseLocale( struct Locale *locale );
ULONG ConvToLower( struct Locale *locale, uint32_t character );
ULONG ConvToUpper( struct Locale *locale, uint32_t character );
void FormatDate( struct Locale *locale, STRPTR fmtTemplate,
	struct DateStamp *date, struct Hook *putCharFunc );
APTR FormatString( struct Locale *locale, STRPTR fmtTemplate, APTR dataStream,
	struct Hook *putCharFunc );
STRPTR GetCatalogStr( struct Catalog *catalog, int32_t stringNum,
	STRPTR defaultString );
STRPTR GetLocaleStr( struct Locale *locale, uint32_t stringNum );
BOOL IsAlNum( struct Locale *locale, uint32_t character );
BOOL IsAlpha( struct Locale *locale, uint32_t character );
BOOL IsCntrl( struct Locale *locale, uint32_t character );
BOOL IsDigit( struct Locale *locale, uint32_t character );
BOOL IsGraph( struct Locale *locale, uint32_t character );
BOOL IsLower( struct Locale *locale, uint32_t character );
BOOL IsPrint( struct Locale *locale, uint32_t character );
BOOL IsPunct( struct Locale *locale, uint32_t character );
BOOL IsSpace( struct Locale *locale, uint32_t character );
BOOL IsUpper( struct Locale *locale, uint32_t character );
BOOL IsXDigit( struct Locale *locale, uint32_t character );
struct Catalog *OpenCatalogA( struct Locale *locale, STRPTR name,
	struct TagItem *tags );
struct Catalog *OpenCatalog( struct Locale *locale, STRPTR name, Tag tag1,
	... );
struct Locale *OpenLocale( STRPTR name );
BOOL ParseDate( struct Locale *locale, struct DateStamp *date,
	STRPTR fmtTemplate, struct Hook *getCharFunc );
ULONG StrConvert( struct Locale *locale, STRPTR string, APTR buffer,
	uint32_t bufferSize, uint32_t type );
LONG StrnCmp( struct Locale *locale, STRPTR string1, STRPTR string2,
	int32_t length, uint32_t type );
#endif	 /* CLIB_LOCALE_PROTOS_H */
