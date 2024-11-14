#ifndef	DATATYPES_SOUNDCLASS_H
#define	DATATYPES_SOUNDCLASS_H
/*
**  $VER: soundclass.h 39.3 (26.4.93)
**  Includes Release 40.15
**
**  Interface definitions for DataType sound objects.
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

#define	SOUNDDTCLASS		"sound.datatype"

/*****************************************************************************/

/* Sound attributes */
#define	SDTA_Dummy		(DTA_Dummy + 500)
#define	SDTA_VoiceHeader	(SDTA_Dummy + 1)
#define	SDTA_Sample		(SDTA_Dummy + 2)
   /* (UBYTE *) Sample data */

#define	SDTA_SampleLength	(SDTA_Dummy + 3)
   /* (ULONG) Length of the sample data in UBYTEs */

#define	SDTA_Period		(SDTA_Dummy + 4)
    /* (UWORD) Period */

#define	SDTA_Volume		(SDTA_Dummy + 5)
    /* (UWORD) Volume.	Range from 0 to 64 */

#define	SDTA_Cycles		(SDTA_Dummy + 6)

/* The following tags are new for V40 */
#define	SDTA_SignalTask		(SDTA_Dummy + 7)
    /* (struct Task *) Task to signal when sound is complete or
	next buffer needed. */

#define	SDTA_SignalBit		(SDTA_Dummy + 8)
    /* (BYTE) Signal bit to use on completion or -1 to disable */

#define	SDTA_Continuous		(SDTA_Dummy + 9)
    /* (ULONG) Playing a continuous stream of data.  Defaults to
	FALSE. */

/*****************************************************************************/

#define CMP_NONE     0
#define CMP_FIBDELTA 1

struct VoiceHeader
{
    ULONG		 vh_OneShotHiSamples;
    ULONG		 vh_RepeatHiSamples;
    ULONG		 vh_SamplesPerHiCycle;
    UWORD		 vh_SamplesPerSec;
    UBYTE		 vh_Octaves;
    UBYTE		 vh_Compression;
    ULONG		 vh_Volume;
};

/*****************************************************************************/

/* IFF types */
#define ID_8SVX MAKE_ID('8','S','V','X')
#define ID_VHDR MAKE_ID('V','H','D','R')
#define ID_BODY MAKE_ID('B','O','D','Y')

/*****************************************************************************/

#endif	/* DATATYPES_SOUNDCLASS_H */
