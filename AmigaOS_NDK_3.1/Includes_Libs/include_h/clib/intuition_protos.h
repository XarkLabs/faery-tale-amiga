#ifndef  CLIB_INTUITION_PROTOS_H
#define  CLIB_INTUITION_PROTOS_H

/*
**	$VER: intuition_protos.h 38.16 (28.8.92)
**	Includes Release 40.15
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 1990-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef  INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef  INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef  INTUITION_CGHOOKS_H
#include <intuition/cghooks.h>
#endif
#ifndef  INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif
/* Public functions OpenIntuition() and Intuition() are intentionally */
/* not documented. */
void OpenIntuition( void );
void Intuition( struct InputEvent *iEvent );
UWORD AddGadget( struct Window *window, struct Gadget *gadget,
	uint32_t position );
BOOL ClearDMRequest( struct Window *window );
void ClearMenuStrip( struct Window *window );
void ClearPointer( struct Window *window );
BOOL CloseScreen( struct Screen *screen );
void CloseWindow( struct Window *window );
LONG CloseWorkBench( void );
void CurrentTime( ULONG *seconds, ULONG *micros );
BOOL DisplayAlert( uint32_t alertNumber, UBYTE *string,
	uint32_t height );
void DisplayBeep( struct Screen *screen );
BOOL DoubleClick( uint32_t sSeconds, uint32_t sMicros,
	uint32_t cSeconds, uint32_t cMicros );
void DrawBorder( struct RastPort *rp, struct Border *border, int32_t leftOffset,
	int32_t topOffset );
void DrawImage( struct RastPort *rp, struct Image *image, int32_t leftOffset,
	int32_t topOffset );
void EndRequest( struct Requester *requester, struct Window *window );
struct Preferences *GetDefPrefs( struct Preferences *preferences, int32_t size );
struct Preferences *GetPrefs( struct Preferences *preferences, int32_t size );
void InitRequester( struct Requester *requester );
struct MenuItem *ItemAddress( struct Menu *menuStrip,
	uint32_t menuNumber );
BOOL ModifyIDCMP( struct Window *window, uint32_t flags );
void ModifyProp( struct Gadget *gadget, struct Window *window,
	struct Requester *requester, uint32_t flags,
	uint32_t horizPot, uint32_t vertPot,
	uint32_t horizBody, uint32_t vertBody );
void MoveScreen( struct Screen *screen, int32_t dx, int32_t dy );
void MoveWindow( struct Window *window, int32_t dx, int32_t dy );
void OffGadget( struct Gadget *gadget, struct Window *window,
	struct Requester *requester );
void OffMenu( struct Window *window, uint32_t menuNumber );
void OnGadget( struct Gadget *gadget, struct Window *window,
	struct Requester *requester );
void OnMenu( struct Window *window, uint32_t menuNumber );
struct Screen *OpenScreen( struct NewScreen *newScreen );
struct Window *OpenWindow( struct NewWindow *newWindow );
ULONG OpenWorkBench( void );
void PrintIText( struct RastPort *rp, struct IntuiText *iText, int32_t left,
	int32_t top );
void RefreshGadgets( struct Gadget *gadgets, struct Window *window,
	struct Requester *requester );
UWORD RemoveGadget( struct Window *window, struct Gadget *gadget );
/* The official calling sequence for ReportMouse is given below. */
/* Note the register order.  For the complete story, read the ReportMouse */
/* autodoc. */
void ReportMouse( int32_t flag, struct Window *window );
void ReportMouse1( struct Window *window, int32_t flag );
BOOL Request( struct Requester *requester, struct Window *window );
void ScreenToBack( struct Screen *screen );
void ScreenToFront( struct Screen *screen );
BOOL SetDMRequest( struct Window *window, struct Requester *requester );
BOOL SetMenuStrip( struct Window *window, struct Menu *menu );
void SetPointer( struct Window *window, UWORD *pointer, int32_t height,
	int32_t width, int32_t xOffset, int32_t yOffset );
void SetWindowTitles( struct Window *window, UBYTE *windowTitle,
	UBYTE *screenTitle );
void ShowTitle( struct Screen *screen, int32_t showIt );
void SizeWindow( struct Window *window, int32_t dx, int32_t dy );
struct View *ViewAddress( void );
struct ViewPort *ViewPortAddress( struct Window *window );
void WindowToBack( struct Window *window );
void WindowToFront( struct Window *window );
BOOL WindowLimits( struct Window *window, int32_t widthMin, int32_t heightMin,
	uint32_t widthMax, uint32_t heightMax );
/*--- start of next generation of names -------------------------------------*/
struct Preferences *SetPrefs( struct Preferences *preferences, int32_t size,
	int32_t inform );
/*--- start of next next generation of names --------------------------------*/
LONG IntuiTextLength( struct IntuiText *iText );
BOOL WBenchToBack( void );
BOOL WBenchToFront( void );
/*--- start of next next next generation of names ---------------------------*/
BOOL AutoRequest( struct Window *window, struct IntuiText *body,
	struct IntuiText *posText, struct IntuiText *negText,
	uint32_t pFlag, uint32_t nFlag, uint32_t width,
	uint32_t height );
void BeginRefresh( struct Window *window );
struct Window *BuildSysRequest( struct Window *window, struct IntuiText *body,
	struct IntuiText *posText, struct IntuiText *negText,
	uint32_t flags, uint32_t width, uint32_t height );
void EndRefresh( struct Window *window, int32_t complete );
void FreeSysRequest( struct Window *window );
/* The return codes for MakeScreen(), RemakeDisplay(), and RethinkDisplay() */
/* are only valid under V39 and greater.  Do not examine them when running */
/* on pre-V39 systems! */
LONG MakeScreen( struct Screen *screen );
LONG RemakeDisplay( void );
LONG RethinkDisplay( void );
/*--- start of next next next next generation of names ----------------------*/
APTR AllocRemember( struct Remember **rememberKey, uint32_t size,
	uint32_t flags );
/* Public function AlohaWorkbench() is intentionally not documented */
void AlohaWorkbench( int32_t wbport );
void FreeRemember( struct Remember **rememberKey, int32_t reallyForget );
/*--- start of 15 Nov 85 names ------------------------*/
ULONG LockIBase( uint32_t dontknow );
void UnlockIBase( uint32_t ibLock );
/*--- functions in V33 or higher (Release 1.2) ---*/
LONG GetScreenData( APTR buffer, uint32_t size, uint32_t type,
	struct Screen *screen );
void RefreshGList( struct Gadget *gadgets, struct Window *window,
	struct Requester *requester, int32_t numGad );
UWORD AddGList( struct Window *window, struct Gadget *gadget,
	uint32_t position, int32_t numGad, struct Requester *requester );
UWORD RemoveGList( struct Window *remPtr, struct Gadget *gadget,
	int32_t numGad );
void ActivateWindow( struct Window *window );
void RefreshWindowFrame( struct Window *window );
BOOL ActivateGadget( struct Gadget *gadgets, struct Window *window,
	struct Requester *requester );
void NewModifyProp( struct Gadget *gadget, struct Window *window,
	struct Requester *requester, uint32_t flags,
	uint32_t horizPot, uint32_t vertPot,
	uint32_t horizBody, uint32_t vertBody, int32_t numGad );
/*--- functions in V36 or higher (Release 2.0) ---*/
LONG QueryOverscan( uint32_t displayID, struct Rectangle *rect,
	int32_t oScanType );
void MoveWindowInFrontOf( struct Window *window,
	struct Window *behindWindow );
void ChangeWindowBox( struct Window *window, int32_t left, int32_t top, int32_t width,
	int32_t height );
struct Hook *SetEditHook( struct Hook *hook );
LONG SetMouseQueue( struct Window *window, uint32_t queueLength );
void ZipWindow( struct Window *window );
/*--- public screens ---*/
struct Screen *LockPubScreen( UBYTE *name );
void UnlockPubScreen( UBYTE *name, struct Screen *screen );
struct List *LockPubScreenList( void );
void UnlockPubScreenList( void );
UBYTE *NextPubScreen( struct Screen *screen, UBYTE *namebuf );
void SetDefaultPubScreen( UBYTE *name );
UWORD SetPubScreenModes( uint32_t modes );
UWORD PubScreenStatus( struct Screen *screen, uint32_t statusFlags );

struct RastPort *ObtainGIRPort( struct GadgetInfo *gInfo );
void ReleaseGIRPort( struct RastPort *rp );
void GadgetMouse( struct Gadget *gadget, struct GadgetInfo *gInfo,
	WORD *mousePoint );
void GetDefaultPubScreen( UBYTE *nameBuffer );
LONG EasyRequestArgs( struct Window *window, struct EasyStruct *easyStruct,
	ULONG *idcmpPtr, APTR args );
LONG EasyRequest( struct Window *window, struct EasyStruct *easyStruct,
	ULONG *idcmpPtr, ... );
struct Window *BuildEasyRequestArgs( struct Window *window,
	struct EasyStruct *easyStruct, uint32_t idcmp, APTR args );
struct Window *BuildEasyRequest( struct Window *window,
	struct EasyStruct *easyStruct, uint32_t idcmp, ... );
LONG SysReqHandler( struct Window *window, ULONG *idcmpPtr, int32_t waitInput );
struct Window *OpenWindowTagList( struct NewWindow *newWindow,
	struct TagItem *tagList );
struct Window *OpenWindowTags( struct NewWindow *newWindow,
	uint32_t tag1Type, ... );
struct Screen *OpenScreenTagList( struct NewScreen *newScreen,
	struct TagItem *tagList );
struct Screen *OpenScreenTags( struct NewScreen *newScreen,
	uint32_t tag1Type, ... );

/*	new Image functions */
void DrawImageState( struct RastPort *rp, struct Image *image, int32_t leftOffset,
	int32_t topOffset, uint32_t state, struct DrawInfo *drawInfo );
BOOL PointInImage( uint32_t point, struct Image *image );
void EraseImage( struct RastPort *rp, struct Image *image, int32_t leftOffset,
	int32_t topOffset );

APTR NewObjectA( struct IClass *classPtr, UBYTE *classID,
	struct TagItem *tagList );
APTR NewObject( struct IClass *classPtr, UBYTE *classID, uint32_t tag1,
	... );

void DisposeObject( APTR object );
ULONG SetAttrsA( APTR object, struct TagItem *tagList );
ULONG SetAttrs( APTR object, uint32_t tag1, ... );

ULONG GetAttr( uint32_t attrID, APTR object, ULONG *storagePtr );

/*	special set attribute call for gadgets */
ULONG SetGadgetAttrsA( struct Gadget *gadget, struct Window *window,
	struct Requester *requester, struct TagItem *tagList );
ULONG SetGadgetAttrs( struct Gadget *gadget, struct Window *window,
	struct Requester *requester, uint32_t tag1, ... );

/*	for class implementors only */
APTR NextObject( APTR objectPtrPtr );
struct IClass *MakeClass( UBYTE *classID, UBYTE *superClassID,
	struct IClass *superClassPtr, uint32_t instanceSize,
	uint32_t flags );
void AddClass( struct IClass *classPtr );


struct DrawInfo *GetScreenDrawInfo( struct Screen *screen );
void FreeScreenDrawInfo( struct Screen *screen, struct DrawInfo *drawInfo );

BOOL ResetMenuStrip( struct Window *window, struct Menu *menu );
void RemoveClass( struct IClass *classPtr );
BOOL FreeClass( struct IClass *classPtr );
/*--- functions in V39 or higher (Release 3) ---*/
struct ScreenBuffer *AllocScreenBuffer( struct Screen *sc, struct BitMap *bm,
	uint32_t flags );
void FreeScreenBuffer( struct Screen *sc, struct ScreenBuffer *sb );
ULONG ChangeScreenBuffer( struct Screen *sc, struct ScreenBuffer *sb );
void ScreenDepth( struct Screen *screen, uint32_t flags, APTR reserved );
void ScreenPosition( struct Screen *screen, uint32_t flags, int32_t x1,
	int32_t y1, int32_t x2, int32_t y2 );
void ScrollWindowRaster( struct Window *win, int32_t dx, int32_t dy, int32_t xMin,
	int32_t yMin, int32_t xMax, int32_t yMax );
void LendMenus( struct Window *fromwindow, struct Window *towindow );
ULONG DoGadgetMethodA( struct Gadget *gad, struct Window *win,
	struct Requester *req, Msg message );
ULONG DoGadgetMethod( struct Gadget *gad, struct Window *win,
	struct Requester *req, uint32_t MethodID, ... );
void SetWindowPointerA( struct Window *win, struct TagItem *taglist );
void SetWindowPointer( struct Window *win, uint32_t tag1, ... );
BOOL TimedDisplayAlert( uint32_t alertNumber, UBYTE *string,
	uint32_t height, uint32_t time );
void HelpControl( struct Window *win, uint32_t flags );
#endif	 /* CLIB_INTUITION_PROTOS_H */
