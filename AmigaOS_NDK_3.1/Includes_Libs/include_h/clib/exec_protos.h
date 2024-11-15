#ifndef  CLIB_EXEC_PROTOS_H
#define  CLIB_EXEC_PROTOS_H

/*
**	$VER: exec_protos.h 39.15 (1.10.93)
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
#ifndef  EXEC_TASKS_H
#include <exec/tasks.h>
#endif
/*------ misc ---------------------------------------------------------*/
ULONG Supervisor( uint32_t (*userFunction)() );
/*------ special patchable hooks to internal exec activity ------------*/
/*------ module creation ----------------------------------------------*/
void InitCode( uint32_t startClass, uint32_t version );
void InitStruct( APTR initTable, APTR memory, uint32_t size );
struct Library *MakeLibrary( APTR funcInit, APTR structInit,
	uint32_t (*libInit)(), uint32_t dataSize,
	uint32_t segList );
void MakeFunctions( APTR target, APTR functionArray,
	uint32_t funcDispBase );
struct Resident *FindResident( UBYTE *name );
APTR InitResident( struct Resident *resident, uint32_t segList );
/*------ diagnostics --------------------------------------------------*/
void Alert( uint32_t alertNum );
void Debug( uint32_t flags );
/*------ interrupts ---------------------------------------------------*/
void Disable( void );
void Enable( void );
void Forbid( void );
void Permit( void );
ULONG SetSR( uint32_t newSR, uint32_t mask );
APTR SuperState( void );
void UserState( APTR sysStack );
struct Interrupt *SetIntVector( int32_t intNumber, struct Interrupt *interrupt );
void AddIntServer( int32_t intNumber, struct Interrupt *interrupt );
void RemIntServer( int32_t intNumber, struct Interrupt *interrupt );
void Cause( struct Interrupt *interrupt );
/*------ memory allocation --------------------------------------------*/
APTR Allocate( struct MemHeader *freeList, uint32_t byteSize );
void Deallocate( struct MemHeader *freeList, APTR memoryBlock,
	uint32_t byteSize );
APTR AllocMem( uint32_t byteSize, uint32_t requirements );
APTR AllocAbs( uint32_t byteSize, APTR location );
void FreeMem( APTR memoryBlock, uint32_t byteSize );
ULONG AvailMem( uint32_t requirements );
struct MemList *AllocEntry( struct MemList *entry );
void FreeEntry( struct MemList *entry );
/*------ lists --------------------------------------------------------*/
void Insert( struct List *list, struct Node *node, struct Node *pred );
void AddHead( struct List *list, struct Node *node );
void AddTail( struct List *list, struct Node *node );
void Remove( struct Node *node );
struct Node *RemHead( struct List *list );
struct Node *RemTail( struct List *list );
void Enqueue( struct List *list, struct Node *node );
struct Node *FindName( struct List *list, UBYTE *name );
/*------ tasks --------------------------------------------------------*/
APTR AddTask( struct Task *task, APTR initPC, APTR finalPC );
void RemTask( struct Task *task );
struct Task *FindTask( UBYTE *name );
BYTE SetTaskPri( struct Task *task, int32_t priority );
ULONG SetSignal( uint32_t newSignals, uint32_t signalSet );
ULONG SetExcept( uint32_t newSignals, uint32_t signalSet );
ULONG Wait( uint32_t signalSet );
void Signal( struct Task *task, uint32_t signalSet );
BYTE AllocSignal( int32_t signalNum );
void FreeSignal( int32_t signalNum );
LONG AllocTrap( int32_t trapNum );
void FreeTrap( int32_t trapNum );
/*------ messages -----------------------------------------------------*/
void AddPort( struct MsgPort *port );
void RemPort( struct MsgPort *port );
void PutMsg( struct MsgPort *port, struct Message *message );
struct Message *GetMsg( struct MsgPort *port );
void ReplyMsg( struct Message *message );
struct Message *WaitPort( struct MsgPort *port );
struct MsgPort *FindPort( UBYTE *name );
/*------ libraries ----------------------------------------------------*/
void AddLibrary( struct Library *library );
void RemLibrary( struct Library *library );
struct Library *OldOpenLibrary( UBYTE *libName );
void CloseLibrary( struct Library *library );
APTR SetFunction( struct Library *library, int32_t funcOffset,
	uint32_t (*newFunction)() );
void SumLibrary( struct Library *library );
/*------ devices ------------------------------------------------------*/
void AddDevice( struct Device *device );
void RemDevice( struct Device *device );
BYTE OpenDevice( char *devName, uint32_t unit,
	struct IORequest *ioRequest, uint32_t flags );	// Xark: UBYTE->char for devName
void CloseDevice( struct IORequest *ioRequest );
BYTE DoIO( struct IORequest *ioRequest );
void SendIO( struct IORequest *ioRequest );
struct IORequest *CheckIO( struct IORequest *ioRequest );
BYTE WaitIO( struct IORequest *ioRequest );
void AbortIO( struct IORequest *ioRequest );
/*------ resources ----------------------------------------------------*/
void AddResource( APTR resource );
void RemResource( APTR resource );
APTR OpenResource( UBYTE *resName );
/*------ private diagnostic support -----------------------------------*/
/*------ misc ---------------------------------------------------------*/
APTR RawDoFmt( UBYTE *formatString, APTR dataStream, void (*putChProc)(),
	APTR putChData );
ULONG GetCC( void );
ULONG TypeOfMem( APTR address );
ULONG Procure( struct SignalSemaphore *sigSem,
	struct SemaphoreMessage *bidMsg );
void Vacate( struct SignalSemaphore *sigSem,
	struct SemaphoreMessage *bidMsg );
struct Library *OpenLibrary( char *libName, uint32_t version );	// Xark: UBYTE->char for libName
/*--- functions in V33 or higher (Release 1.2) ---*/
/*------ signal semaphores (note funny registers)----------------------*/
void InitSemaphore( struct SignalSemaphore *sigSem );
void ObtainSemaphore( struct SignalSemaphore *sigSem );
void ReleaseSemaphore( struct SignalSemaphore *sigSem );
ULONG AttemptSemaphore( struct SignalSemaphore *sigSem );
void ObtainSemaphoreList( struct List *sigSem );
void ReleaseSemaphoreList( struct List *sigSem );
struct SignalSemaphore *FindSemaphore( UBYTE *sigSem );
void AddSemaphore( struct SignalSemaphore *sigSem );
void RemSemaphore( struct SignalSemaphore *sigSem );
/*------ kickmem support ----------------------------------------------*/
ULONG SumKickData( void );
/*------ more memory support ------------------------------------------*/
void AddMemList( uint32_t size, uint32_t attributes, int32_t pri,
	APTR base, UBYTE *name );
void CopyMem( APTR source, APTR dest, uint32_t size );
void CopyMemQuick( APTR source, APTR dest, uint32_t size );
/*------ cache --------------------------------------------------------*/
/*--- functions in V36 or higher (Release 2.0) ---*/
void CacheClearU( void );
void CacheClearE( APTR address, uint32_t length, uint32_t caches );
ULONG CacheControl( uint32_t cacheBits, uint32_t cacheMask );
/*------ misc ---------------------------------------------------------*/
APTR CreateIORequest( struct MsgPort *port, uint32_t size );
void DeleteIORequest( APTR iorequest );
struct MsgPort *CreateMsgPort( void );
void DeleteMsgPort( struct MsgPort *port );
void ObtainSemaphoreShared( struct SignalSemaphore *sigSem );
/*------ even more memory support -------------------------------------*/
APTR AllocVec( uint32_t byteSize, uint32_t requirements );
void FreeVec( APTR memoryBlock );
/*------ V39 Pool LVOs...*/
APTR CreatePool( uint32_t requirements, uint32_t puddleSize,
	uint32_t threshSize );
void DeletePool( APTR poolHeader );
APTR AllocPooled( APTR poolHeader, uint32_t memSize );
void FreePooled( APTR poolHeader, APTR memory, uint32_t memSize );
/*------ misc ---------------------------------------------------------*/
ULONG AttemptSemaphoreShared( struct SignalSemaphore *sigSem );
void ColdReboot( void );
void StackSwap( struct StackSwapStruct *newStack );
/*------ task trees ---------------------------------------------------*/
void ChildFree( APTR tid );
void ChildOrphan( APTR tid );
void ChildStatus( APTR tid );
void ChildWait( APTR tid );
/*------ future expansion ---------------------------------------------*/
APTR CachePreDMA( APTR address, ULONG *length, uint32_t flags );
void CachePostDMA( APTR address, ULONG *length, uint32_t flags );
/*------ New, for V39*/
/*--- functions in V39 or higher (Release 3) ---*/
/*------ Low memory handler functions*/
void AddMemHandler( struct Interrupt *memhand );
void RemMemHandler( struct Interrupt *memhand );
/*------ Function to attempt to obtain a Quick Interrupt Vector...*/
ULONG ObtainQuickVector( APTR interruptCode );
#endif	 /* CLIB_EXEC_PROTOS_H */
