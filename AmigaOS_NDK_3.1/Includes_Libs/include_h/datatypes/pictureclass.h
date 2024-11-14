#ifndef	DATATYPES_PICTURECLASS_H
#define	DATATYPES_PICTURECLASS_H
/*
**  $VER: pictureclass.h 39.5 (28.4.93)
**  Includes Release 40.15
**
**  Interface definitions for DataType picture objects.
**
**  (C) Copyright 1992-1993 Commodore-Amiga, Inc.
**	All Rights Reserved
*/

#ifndef	UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#ifndef	DATATYPES_DATATYPESCLASS_H
#include <datatypes/datatypesclass.h>
#endif

#ifndef	LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

/*****************************************************************************/

#define	PICTUREDTCLASS		"picture.datatype"

/*****************************************************************************/

/* Picture attributes */
#define	PDTA_ModeID		(DTA_Dummy + 200)
	/* Mode ID of the picture */

#define	PDTA_BitMapHeader	(DTA_Dummy + 201)

#define	PDTA_BitMap		(DTA_Dummy + 202)
	/* Pointer to a class-allocated bitmap, that will end
	 * up being freed by picture.class when DisposeDTObject()
	 * is called */

#define	PDTA_ColorRegisters	(DTA_Dummy + 203)
#define	PDTA_CRegs		(DTA_Dummy + 204)
#define	PDTA_GRegs		(DTA_Dummy + 205)
#define	PDTA_ColorTable		(DTA_Dummy + 206)
#define	PDTA_ColorTable2	(DTA_Dummy + 207)
#define	PDTA_Allocated		(DTA_Dummy + 208)
#define	PDTA_NumColors		(DTA_Dummy + 209)
#define	PDTA_NumAlloc		(DTA_Dummy + 210)

#define	PDTA_Remap		(DTA_Dummy + 211)
	/* Boolean : Remap picture (defaults to TRUE) */

#define	PDTA_Screen		(DTA_Dummy + 212)
	/* Screen to remap to */

#define	PDTA_FreeSourceBitMap	(DTA_Dummy + 213)
	/* Boolean : Free the source bitmap after remapping */

#define	PDTA_Grab		(DTA_Dummy + 214)
	/* Pointer to a Point structure */

#define	PDTA_DestBitMap		(DTA_Dummy + 215)
	/* Pointer to the destination (remapped) bitmap */

#define	PDTA_ClassBitMap	(DTA_Dummy + 216)
	/* Pointer to class-allocated bitmap, that will end
	 * up being freed by the class after DisposeDTObject()
	 * is called */

#define	PDTA_NumSparse		(DTA_Dummy + 217)
	/* (UWORD) Number of colors used for sparse remapping */

#define	PDTA_SparseTable	(DTA_Dummy + 218)
	/* (UBYTE *) Pointer to a table of pen numbers indicating
	 * which colors should be used when remapping the image.
	 * This array must contain as many entries as there
	 * are colors specified with PDTA_NumSparse */

/*****************************************************************************/

/*  Masking techniques	*/
#define	mskNone			0
#define	mskHasMask		1
#define	mskHasTransparentColor	2
#define	mskLasso		3
#define	mskHasAlpha		4

/*  Compression techniques  */
#define	cmpNone			0
#define	cmpByteRun1		1
#define	cmpByteRun2		2

/*  Bitmap header (BMHD) structure  */
struct BitMapHeader
{
    UWORD	 bmh_Width;		/* Width in pixels */
    UWORD	 bmh_Height;		/* Height in pixels */
    WORD	 bmh_Left;		/* Left position */
    WORD	 bmh_Top;		/* Top position */
    UBYTE	 bmh_Depth;		/* Number of planes */
    UBYTE	 bmh_Masking;		/* Masking type */
    UBYTE	 bmh_Compression;	/* Compression type */
    UBYTE	 bmh_Pad;
    UWORD	 bmh_Transparent;	/* Transparent color */
    UBYTE	 bmh_XAspect;
    UBYTE	 bmh_YAspect;
    WORD	 bmh_PageWidth;
    WORD	 bmh_PageHeight;
};

/*****************************************************************************/

/*  Color register structure */
struct ColorRegister
{
    UBYTE red, green, blue;
};

/*****************************************************************************/

/* IFF types that may be in pictures */
#define	ID_ILBM		MAKE_ID('I','L','B','M')
#define	ID_BMHD		MAKE_ID('B','M','H','D')
#define	ID_BODY		MAKE_ID('B','O','D','Y')
#define	ID_CMAP		MAKE_ID('C','M','A','P')
#define	ID_CRNG		MAKE_ID('C','R','N','G')
#define	ID_GRAB		MAKE_ID('G','R','A','B')
#define	ID_SPRT		MAKE_ID('S','P','R','T')
#define	ID_DEST		MAKE_ID('D','E','S','T')
#define	ID_CAMG		MAKE_ID('C','A','M','G')

#endif	/* DATATYPES_PICTURECLASS_H */
