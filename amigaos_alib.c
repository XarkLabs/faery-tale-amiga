// amigaos_alib.c
#include "amiga39.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// TODO: BeginIO -- initiate asynchronous device I/O
void BeginIO(struct IORequest * ioReq)
{
    (void)ioReq;
    RUNLOGF("<= alib.BeginIO(%p) STUB", ioReq);
}

// TODO: CheckIO -- get the status of an IORequest
struct IORequest * CheckIO(struct IORequest * ioReq)
{
    struct IORequest * res = NULL;
    (void)ioReq;
    RUNLOGF("%p <= alib.CheckIO(%p) STUB", res, ioReq);
    return res;
}

// TODO: CreateExtIO -- create an IORequest structure
struct IORequest * CreateExtIO(struct MsgPort * port, int32_t ioSize)
{
    struct IORequest * res = NULL;
    (void)port;
    (void)ioSize;
    RUNLOGF("%p <= alib.CreateExtIO(%p, %d) STUB", res, port, ioSize);
    return res;
}

// TODO: CreatePort - Allocate and initialize a new message port
struct MsgPort * CreatePort(STRPTR name, int32_t pri)
{
    struct MsgPort * res = NULL;
    (void)name;
    (void)pri;
    RUNLOGF("%p <= alib.CreatePort(\"%s\", %d) STUB", res, name, pri);
    return res;
}

// TODO: CreateStdIO -- create an IOStdReq structure
struct IOStdReq * CreateStdIO(struct MsgPort * port)
{
    struct IOStdReq * res = NULL;
    (void)port;
    RUNLOGF("%p <= alib.CreateStdIO(%p) STUB", res, port);
    return res;
}

// TODO: DeleteExtIO - return memory allocated for extended IO request
void DeleteExtIO(struct IORequest * ioReq)
{
    (void)ioReq;
    RUNLOGF("<= alib.DeleteExtIO(%p) STUB", ioReq);
}

// TODO: DeletePort - free a message port created by CreatePort()
void DeletePort(struct MsgPort * ioReq)
{
    (void)ioReq;
    RUNLOGF("<= alib.DeletePort(%p) STUB", ioReq);
}

// TODO: DeleteStdIO - return memory allocated for IOStdReq
void DeleteStdIO(struct IOStdReq * ioReq)
{
    (void)ioReq;
    RUNLOGF("<= alib.DeleteStdIO(%p) STUB", ioReq);
}

// EOF
