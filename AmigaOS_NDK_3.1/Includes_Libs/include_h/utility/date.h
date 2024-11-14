#ifndef UTILITY_DATE_H
#define UTILITY_DATE_H
/*
**	$VER: date.h 39.1 (20.1.92)
**	Includes Release 40.15
**
**	Date conversion routines ClockData definition.
**
**	(C) Copyright 1989-1993 Commodore-Amiga Inc.
**	All Rights Reserved
*/

/*****************************************************************************/


#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif


/*****************************************************************************/


struct ClockData
{
    UWORD sec;
    UWORD min;
    UWORD hour;
    UWORD mday;
    UWORD month;
    UWORD year;
    UWORD wday;
};


/*****************************************************************************/


#endif /* UTILITY_DATE_H */
