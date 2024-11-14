// amigaos_alib.c
#include "amiga39.h"

#include <stdlib.h>
#include <stdio.h>

// BeginIO(ioReq)
void BeginIO(struct IORequest *req)
{
    // TODO: BeginIO
    (void)req;
    RUNLOGF("<= alib.BeginIO(%p)", req);
}
