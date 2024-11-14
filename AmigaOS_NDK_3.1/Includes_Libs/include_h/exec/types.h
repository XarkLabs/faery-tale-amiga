// Xark: Modified to use stdint.h sizes

#ifndef	EXEC_TYPES_H
#define	EXEC_TYPES_H

#include <stdint.h>
/*
**	$VER: types.h 40.1 (10.8.93)
**	Includes Release 40.15
**
**	Data typing.  Must be included before any other Amiga include.
**
**	(C) Copyright 1985-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/


#define INCLUDE_VERSION	40 /* Version of the include files in use. (Do not
			      use this label for OpenLibrary() calls!) */


#define GLOBAL	extern	    /* the declaratory use of an external */
#define IMPORT	extern	    /* reference to an external */
#define STATIC	static	    /* a local static variable */
#define REGISTER register   /* a (hopefully) register variable */


#ifndef VOID
#define VOID		void
#endif


  /*  WARNING: APTR was redefined for the V36 Includes!  APTR is a   */
 /*  32-Bit Absolute Memory Pointer.  C pointer math will not	    */
/*  operate on APTR --	use "ULONG *" instead.			   */
#ifndef APTR_TYPEDEF
#define APTR_TYPEDEF
typedef void	       *APTR;	    /* 32-bit untyped pointer */
#endif
typedef int32_t		LONG;	    /* signed 32-bit quantity */
typedef uint32_t	ULONG;	    /* unsigned 32-bit quantity */
typedef uint32_t	LONGBITS;   /* 32 bits manipulated individually */
typedef int16_t		WORD;	    /* signed 16-bit quantity */
typedef uint16_t	UWORD;	    /* unsigned 16-bit quantity */
typedef uint16_t	WORDBITS;   /* 16 bits manipulated individually */
#if __STDC__
typedef int8_t	BYTE;	    /* signed 8-bit quantity */
#else
typedef char		BYTE;	    /* signed 8-bit quantity */
#endif
typedef uint8_t	UBYTE;	    /* unsigned 8-bit quantity */
typedef uint8_t	BYTEBITS;   /* 8 bits manipulated individually */
typedef uint16_t	RPTR;	    /* signed relative pointer */

#ifdef __cplusplus
typedef char	       *STRPTR;     /* string pointer (NULL terminated) */
#elif defined(__clang__)          /* Xark: avoid conversion issues */
typedef char	       *STRPTR;     /* string pointer (NULL terminated) */
#else
typedef uint8_t  *STRPTR;     /* string pointer (NULL terminated) */
#endif


/* For compatibility only: (don't use in new code) */
typedef int16_t		SHORT;	    /* signed 16-bit quantity (use WORD) */
typedef uint16_t	USHORT;     /* unsigned 16-bit quantity (use UWORD) */
typedef int16_t		COUNT;
typedef uint16_t	UCOUNT;
typedef ULONG		CPTR;


/* Types with specific semantics */
typedef float		FLOAT;
typedef double		DOUBLE;
typedef int16_t		BOOL;
typedef uint8_t	TEXT;

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0L
#endif


#define BYTEMASK	0xFF


 /* #define LIBRARY_VERSION is now obsolete.  Please use LIBRARY_MINIMUM */
/* or code the specific minimum library version you require.		*/
#define LIBRARY_MINIMUM	33 /* Lowest version supported by Commodore-Amiga */


#endif	/* EXEC_TYPES_H */
