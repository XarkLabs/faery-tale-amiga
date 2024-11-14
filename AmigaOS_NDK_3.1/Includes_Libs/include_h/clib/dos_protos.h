#ifndef  CLIB_DOS_PROTOS_H
#define  CLIB_DOS_PROTOS_H

/*
**	$VER: dos_protos.h 36.31 (17.12.92)
**	Includes Release 40.15
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 1990-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef  DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef  DOS_DOSEXTENS_H
#include <dos/dosextens.h>
#endif
#ifndef  DOS_RECORD_H
#include <dos/record.h>
#endif
#ifndef  DOS_RDARGS_H
#include <dos/rdargs.h>
#endif
#ifndef  DOS_DOSASL_H
#include <dos/dosasl.h>
#endif
#ifndef  DOS_VAR_H
#include <dos/var.h>
#endif
#ifndef  DOS_NOTIFY_H
#include <dos/notify.h>
#endif
#ifndef  DOS_DATETIME_H
#include <dos/datetime.h>
#endif
BPTR Open( STRPTR name, int32_t accessMode );
LONG Close( BPTR file );
LONG Read( BPTR file, APTR buffer, int32_t length );
LONG Write( BPTR file, APTR buffer, int32_t length );
BPTR Input( void );
BPTR Output( void );
LONG Seek( BPTR file, int32_t position, int32_t offset );
LONG DeleteFile( STRPTR name );
LONG Rename( STRPTR oldName, STRPTR newName );
BPTR Lock( STRPTR name, int32_t type );
void UnLock( BPTR lock );
BPTR DupLock( BPTR lock );
LONG Examine( BPTR lock, struct FileInfoBlock *fileInfoBlock );
LONG ExNext( BPTR lock, struct FileInfoBlock *fileInfoBlock );
LONG Info( BPTR lock, struct InfoData *parameterBlock );
BPTR CreateDir( STRPTR name );
BPTR CurrentDir( BPTR lock );
LONG IoErr( void );
struct MsgPort *CreateProc( STRPTR name, int32_t pri, BPTR segList,
	int32_t stackSize );
void Exit( int32_t returnCode );
BPTR LoadSeg( STRPTR name );
void UnLoadSeg( BPTR seglist );
struct MsgPort *DeviceProc( STRPTR name );
LONG SetComment( STRPTR name, STRPTR comment );
LONG SetProtection( STRPTR name, int32_t protect );
struct DateStamp *DateStamp( struct DateStamp *date );
void Delay( int32_t timeout );
LONG WaitForChar( BPTR file, int32_t timeout );
BPTR ParentDir( BPTR lock );
LONG IsInteractive( BPTR file );
LONG Execute( STRPTR string, BPTR file, BPTR file2 );
/*--- functions in V36 or higher (Release 2.0) ---*/
/*	DOS Object creation/deletion */
APTR AllocDosObject( uint32_t type, struct TagItem *tags );
APTR AllocDosObjectTagList( uint32_t type, struct TagItem *tags );
APTR AllocDosObjectTags( uint32_t type, uint32_t tag1type, ... );
void FreeDosObject( uint32_t type, APTR ptr );
/*	Packet Level routines */
LONG DoPkt( struct MsgPort *port, int32_t action, int32_t arg1, int32_t arg2, int32_t arg3,
	int32_t arg4, int32_t arg5 );
LONG DoPkt0( struct MsgPort *port, int32_t action );
LONG DoPkt1( struct MsgPort *port, int32_t action, int32_t arg1 );
LONG DoPkt2( struct MsgPort *port, int32_t action, int32_t arg1, int32_t arg2 );
LONG DoPkt3( struct MsgPort *port, int32_t action, int32_t arg1, int32_t arg2,
	int32_t arg3 );
LONG DoPkt4( struct MsgPort *port, int32_t action, int32_t arg1, int32_t arg2,
	int32_t arg3, int32_t arg4 );
void SendPkt( struct DosPacket *dp, struct MsgPort *port,
	struct MsgPort *replyport );
struct DosPacket *WaitPkt( void );
void ReplyPkt( struct DosPacket *dp, int32_t res1, int32_t res2 );
void AbortPkt( struct MsgPort *port, struct DosPacket *pkt );
/*	Record Locking */
BOOL LockRecord( BPTR fh, uint32_t offset, uint32_t length,
	uint32_t mode, uint32_t timeout );
BOOL LockRecords( struct RecordLock *recArray, uint32_t timeout );
BOOL UnLockRecord( BPTR fh, uint32_t offset, uint32_t length );
BOOL UnLockRecords( struct RecordLock *recArray );
/*	Buffered File I/O */
BPTR SelectInput( BPTR fh );
BPTR SelectOutput( BPTR fh );
LONG FGetC( BPTR fh );
LONG FPutC( BPTR fh, int32_t ch );
LONG UnGetC( BPTR fh, int32_t character );
LONG FRead( BPTR fh, APTR block, uint32_t blocklen,
	uint32_t number );
LONG FWrite( BPTR fh, APTR block, uint32_t blocklen,
	uint32_t number );
STRPTR FGets( BPTR fh, STRPTR buf, uint32_t buflen );
LONG FPuts( BPTR fh, STRPTR str );
void VFWritef( BPTR fh, STRPTR format, LONG *argarray );
void FWritef( BPTR fh, STRPTR format, ... );
LONG VFPrintf( BPTR fh, STRPTR format, APTR argarray );
LONG FPrintf( BPTR fh, STRPTR format, ... );
LONG Flush( BPTR fh );
LONG SetVBuf( BPTR fh, STRPTR buff, int32_t type, int32_t size );
/*	DOS Object Management */
BPTR DupLockFromFH( BPTR fh );
BPTR OpenFromLock( BPTR lock );
BPTR ParentOfFH( BPTR fh );
BOOL ExamineFH( BPTR fh, struct FileInfoBlock *fib );
LONG SetFileDate( STRPTR name, struct DateStamp *date );
LONG NameFromLock( BPTR lock, STRPTR buffer, int32_t len );
LONG NameFromFH( BPTR fh, STRPTR buffer, int32_t len );
WORD SplitName( STRPTR name, uint32_t seperator, STRPTR buf, int32_t oldpos,
	int32_t size );
LONG SameLock( BPTR lock1, BPTR lock2 );
LONG SetMode( BPTR fh, int32_t mode );
LONG ExAll( BPTR lock, struct ExAllData *buffer, int32_t size, int32_t data,
	struct ExAllControl *control );
LONG ReadLink( struct MsgPort *port, BPTR lock, STRPTR path, STRPTR buffer,
	uint32_t size );
LONG MakeLink( STRPTR name, int32_t dest, int32_t soft );
LONG ChangeMode( int32_t type, BPTR fh, int32_t newmode );
LONG SetFileSize( BPTR fh, int32_t pos, int32_t mode );
/*	Error Handling */
LONG SetIoErr( int32_t result );
BOOL Fault( int32_t code, STRPTR header, STRPTR buffer, int32_t len );
BOOL PrintFault( int32_t code, STRPTR header );
LONG ErrorReport( int32_t code, int32_t type, uint32_t arg1,
	struct MsgPort *device );
/*	Process Management */
struct CommandLineInterface *Cli( void );
struct Process *CreateNewProc( struct TagItem *tags );
struct Process *CreateNewProcTagList( struct TagItem *tags );
struct Process *CreateNewProcTags( uint32_t tag1type, ... );
LONG RunCommand( BPTR seg, int32_t stack, STRPTR paramptr, int32_t paramlen );
struct MsgPort *GetConsoleTask( void );
struct MsgPort *SetConsoleTask( struct MsgPort *task );
struct MsgPort *GetFileSysTask( void );
struct MsgPort *SetFileSysTask( struct MsgPort *task );
STRPTR GetArgStr( void );
BOOL SetArgStr( STRPTR string );
struct Process *FindCliProc( uint32_t num );
ULONG MaxCli( void );
BOOL SetCurrentDirName( STRPTR name );
BOOL GetCurrentDirName( STRPTR buf, int32_t len );
BOOL SetProgramName( STRPTR name );
BOOL GetProgramName( STRPTR buf, int32_t len );
BOOL SetPrompt( STRPTR name );
BOOL GetPrompt( STRPTR buf, int32_t len );
BPTR SetProgramDir( BPTR lock );
BPTR GetProgramDir( void );
/*	Device List Management */
LONG SystemTagList( STRPTR command, struct TagItem *tags );
LONG System( STRPTR command, struct TagItem *tags );
LONG SystemTags( STRPTR command, uint32_t tag1type, ... );
LONG AssignLock( STRPTR name, BPTR lock );
BOOL AssignLate( STRPTR name, STRPTR path );
BOOL AssignPath( STRPTR name, STRPTR path );
BOOL AssignAdd( STRPTR name, BPTR lock );
LONG RemAssignList( STRPTR name, BPTR lock );
struct DevProc *GetDeviceProc( STRPTR name, struct DevProc *dp );
void FreeDeviceProc( struct DevProc *dp );
struct DosList *LockDosList( uint32_t flags );
void UnLockDosList( uint32_t flags );
struct DosList *AttemptLockDosList( uint32_t flags );
BOOL RemDosEntry( struct DosList *dlist );
LONG AddDosEntry( struct DosList *dlist );
struct DosList *FindDosEntry( struct DosList *dlist, STRPTR name,
	uint32_t flags );
struct DosList *NextDosEntry( struct DosList *dlist, uint32_t flags );
struct DosList *MakeDosEntry( STRPTR name, int32_t type );
void FreeDosEntry( struct DosList *dlist );
BOOL IsFileSystem( STRPTR name );
/*	Handler Interface */
BOOL Format( STRPTR filesystem, STRPTR volumename, uint32_t dostype );
LONG Relabel( STRPTR drive, STRPTR newname );
LONG Inhibit( STRPTR name, int32_t onoff );
LONG AddBuffers( STRPTR name, int32_t number );
/*	Date, Time Routines */
LONG CompareDates( struct DateStamp *date1, struct DateStamp *date2 );
LONG DateToStr( struct DateTime *datetime );
LONG StrToDate( struct DateTime *datetime );
/*	Image Management */
BPTR InternalLoadSeg( BPTR fh, BPTR table, LONG *funcarray, LONG *stack );
BOOL InternalUnLoadSeg( BPTR seglist, void (*freefunc)() );
BPTR NewLoadSeg( STRPTR file, struct TagItem *tags );
BPTR NewLoadSegTagList( STRPTR file, struct TagItem *tags );
BPTR NewLoadSegTags( STRPTR file, uint32_t tag1type, ... );
LONG AddSegment( STRPTR name, BPTR seg, int32_t system );
struct Segment *FindSegment( STRPTR name, struct Segment *seg, int32_t system );
LONG RemSegment( struct Segment *seg );
/*	Command Support */
LONG CheckSignal( int32_t mask );
struct RDArgs *ReadArgs( STRPTR arg_template, LONG *array,
	struct RDArgs *args );
LONG FindArg( STRPTR keyword, STRPTR arg_template );
LONG ReadItem( STRPTR name, int32_t maxchars, struct CSource *cSource );
LONG StrToLong( STRPTR string, LONG *value );
LONG MatchFirst( STRPTR pat, struct AnchorPath *anchor );
LONG MatchNext( struct AnchorPath *anchor );
void MatchEnd( struct AnchorPath *anchor );
LONG ParsePattern( STRPTR pat, STRPTR buf, int32_t buflen );
BOOL MatchPattern( STRPTR pat, STRPTR str );
void FreeArgs( struct RDArgs *args );
STRPTR FilePart( STRPTR path );
STRPTR PathPart( STRPTR path );
BOOL AddPart( STRPTR dirname, STRPTR filename, uint32_t size );
/*	Notification */
BOOL StartNotify( struct NotifyRequest *notify );
void EndNotify( struct NotifyRequest *notify );
/*	Environment Variable functions */
BOOL SetVar( STRPTR name, STRPTR buffer, int32_t size, int32_t flags );
LONG GetVar( STRPTR name, STRPTR buffer, int32_t size, int32_t flags );
LONG DeleteVar( STRPTR name, uint32_t flags );
struct LocalVar *FindVar( STRPTR name, uint32_t type );
LONG CliInitNewcli( struct DosPacket *dp );
LONG CliInitRun( struct DosPacket *dp );
LONG WriteChars( STRPTR buf, uint32_t buflen );
LONG PutStr( STRPTR str );
LONG VPrintf( STRPTR format, APTR argarray );
LONG Printf( STRPTR format, ... );
/* these were unimplemented until dos 36.147 */
LONG ParsePatternNoCase( STRPTR pat, STRPTR buf, int32_t buflen );
BOOL MatchPatternNoCase( STRPTR pat, STRPTR str );
/* this was added for V37 dos, returned 0 before then. */
BOOL SameDevice( BPTR lock1, BPTR lock2 );

/* NOTE: the following entries did NOT exist before ks 36.303 (2.02) */
/* If you are going to use them, open dos.library with version 37 */

/* These calls were added for V39 dos: */
void ExAllEnd( BPTR lock, struct ExAllData *buffer, int32_t size, int32_t data,
	struct ExAllControl *control );
BOOL SetOwner( STRPTR name, int32_t owner_info );
#endif	 /* CLIB_DOS_PROTOS_H */
