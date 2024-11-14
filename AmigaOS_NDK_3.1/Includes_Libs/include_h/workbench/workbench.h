#ifndef WORKBENCH_WORKBENCH_H
#define WORKBENCH_WORKBENCH_H
/*
**	$VER: workbench.h 40.1 (26.8.93)
**	Includes Release 40.15
**
**	workbench.library general definitions
**
**	(C) Copyright 1985-1993 Commodore-Amiga, Inc.
**	All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include "exec/types.h"
#endif

#ifndef	EXEC_NODES_H
#include "exec/nodes.h"
#endif

#ifndef	EXEC_LISTS_H
#include "exec/lists.h"
#endif

#ifndef EXEC_TASKS_H
#include "exec/tasks.h"
#endif

#ifndef INTUITION_INTUITION_H
#include "intuition/intuition.h"
#endif

#define	WBDISK		1
#define	WBDRAWER	2
#define	WBTOOL		3
#define	WBPROJECT	4
#define	WBGARBAGE	5
#define	WBDEVICE	6
#define	WBKICK		7
#define WBAPPICON	8

struct OldDrawerData { /* pre V36 definition */
    struct NewWindow	dd_NewWindow;	/* args to open window */
    LONG		dd_CurrentX;	/* current x coordinate of origin */
    LONG		dd_CurrentY;	/* current y coordinate of origin */
};
/* the amount of DrawerData actually written to disk */
#define OLDDRAWERDATAFILESIZE	(sizeof(struct OldDrawerData))

struct DrawerData {
    struct NewWindow	dd_NewWindow;	/* args to open window */
    LONG		dd_CurrentX;	/* current x coordinate of origin */
    LONG		dd_CurrentY;	/* current y coordinate of origin */
    ULONG		dd_Flags;	/* flags for drawer */
    UWORD		dd_ViewModes;	/* view mode for drawer */
};
/* the amount of DrawerData actually written to disk */
#define DRAWERDATAFILESIZE	(sizeof(struct DrawerData))

struct DiskObject {
    UWORD		do_Magic; /* a magic number at the start of the file */
    UWORD		do_Version; /* a version number, so we can change it */
    struct Gadget	do_Gadget;	/* a copy of in core gadget */
    UBYTE		do_Type;
    char *		do_DefaultTool;
    char **		do_ToolTypes;
    LONG		do_CurrentX;
    LONG		do_CurrentY;
    struct DrawerData *	do_DrawerData;
    char *		do_ToolWindow;	/* only applies to tools */
    LONG		do_StackSize;	/* only applies to tools */

};

#define WB_DISKMAGIC	0xe310	/* a magic number, not easily impersonated */
#define WB_DISKVERSION	1	/* our current version number */
#define WB_DISKREVISION	1	/* our current revision number */
/* I only use the lower 8 bits of Gadget.UserData for the revision # */
#define WB_DISKREVISIONMASK	255

struct FreeList {
    WORD		fl_NumFree;
    struct List		fl_MemList;
};

/* workbench does different complement modes for its gadgets.
** It supports separate images, complement mode, and backfill mode.
** The first two are identical to intuitions GFLG_GADGIMAGE and GFLG_GADGHCOMP.
** backfill is similar to GFLG_GADGHCOMP, but the region outside of the
** image (which normally would be color three when complemented)
** is flood-filled to color zero.
*/
#define GFLG_GADGBACKFILL 0x0001
#define GADGBACKFILL	  0x0001    /* an old synonym */

/* if an icon does not really live anywhere, set its current position
** to here
*/
#define NO_ICON_POSITION	(0x80000000)

/* workbench now is a library.	this is it's name */
#define WORKBENCH_NAME		"workbench.library"

/* If you find am_Version >= AM_VERSION, you know this structure has
 * at least the fields defined in this version of the include file
 */
#define	AM_VERSION	1

struct AppMessage {
    struct Message am_Message;	/* standard message structure */
    UWORD am_Type;		/* message type */
    ULONG am_UserData;		/* application specific */
    ULONG am_ID;		/* application definable ID */
    LONG am_NumArgs;		/* # of elements in arglist */
    struct WBArg *am_ArgList;	/* the arguements themselves */
    UWORD am_Version;		/* will be AM_VERSION */
    UWORD am_Class;		/* message class */
    WORD am_MouseX;		/* mouse x position of event */
    WORD am_MouseY;		/* mouse y position of event */
    ULONG am_Seconds;		/* current system clock time */
    ULONG am_Micros;		/* current system clock time */
    ULONG am_Reserved[8];	/* avoid recompilation */
};

/* types of app messages */
#define AMTYPE_APPWINDOW   7	/* app window message	 */
#define AMTYPE_APPICON	   8	/* app icon message	 */
#define AMTYPE_APPMENUITEM 9	/* app menu item message */


/*
 * The following structures are private.  These are just stub
 * structures for code compatibility...
 */
struct	AppWindow	{ void *aw_PRIVATE;  };
struct	AppIcon		{ void *ai_PRIVATE;  };
struct		AppMenuItem	{ void *ami_PRIVATE; };

#endif	/* !WORKBENCH_WORKBENCH_H */
