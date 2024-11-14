#ifndef WORKBENCH_STARTUP_H
#define WORKBENCH_STARTUP_H
/*
**	$VER: startup.h 36.3 (11.7.90)
**	Includes Release 40.15
**
**	workbench startup definitions
**
**	(C) Copyright 1985-1993 Commodore-Amiga, Inc.
**	All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include "exec/types.h"
#endif

#ifndef EXEC_PORTS_H
#include "exec/ports.h"
#endif

#ifndef LIBRARIES_DOS_H
#include "libraries/dos.h"
#endif

struct WBStartup {
    struct Message	sm_Message;	/* a standard message structure */
    struct MsgPort *	sm_Process;	/* the process descriptor for you */
    BPTR		sm_Segment;	/* a descriptor for your code */
    LONG		sm_NumArgs;	/* the number of elements in ArgList */
    char *		sm_ToolWindow;	/* description of window */
    struct WBArg *	sm_ArgList;	/* the arguments themselves */
};

struct WBArg {
    BPTR		wa_Lock;	/* a lock descriptor */
    BYTE *		wa_Name;	/* a string relative to that lock */
};

#endif	/* !WORKBENCH_STARTUP_H */
