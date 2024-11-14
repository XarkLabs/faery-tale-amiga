#ifndef PREFS_WBPATTERN_H
#define PREFS_WBPATTERN_H
/*
**	$VER: wbpattern.h 39.4 (11.6.92)
**	Includes Release 40.15
**
**	File format for wbpattern preferences
**
**	(C) Copyright 1991-1993 Commodore-Amiga, Inc.
**	All Rights Reserved
*/

/*****************************************************************************/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

/*****************************************************************************/

#define ID_PTRN MAKE_ID('P','T','R','N')

/*****************************************************************************/

struct WBPatternPrefs
{
    ULONG	 wbp_Reserved[4];
    UWORD	 wbp_Which;			/* Which pattern is it */
    UWORD	 wbp_Flags;
    BYTE	 wbp_Revision;			/* Must be set to zero */
    BYTE	 wbp_Depth;			/* Depth of pattern */
    UWORD	 wbp_DataLength;		/* Length of following data */
};

/*****************************************************************************/

/* constants for WBPatternPrefs.wbp_Which */
#define	WBP_ROOT	0
#define	WBP_DRAWER	1
#define	WBP_SCREEN	2

/* wbp_Flags values */
#define	WBPF_PATTERN	0x0001
    /* Data contains a pattern */

#define	WBPF_NOREMAP	0x0010
    /* Don't remap the pattern */

/*****************************************************************************/

#define MAXDEPTH	3	/*  Max depth supported (8 colors) */
#define DEFPATDEPTH	2	/*  Depth of default patterns */

/*  Pattern width & height: */
#define PAT_WIDTH	16
#define PAT_HEIGHT	16

/*****************************************************************************/

#endif /* PREFS_WBPATTERN_H */
