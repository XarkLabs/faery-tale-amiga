// amigaos_exec.c
#include "amiga39.h"

#include <stdlib.h> // Xark: Added
#include <stdio.h>  // Xark: Added

// memoryBlock = AllocMem(byteSize, attributes)
APTR AllocMem(ULONG bytesize, ULONG attributes)
{
    void *ptr = calloc(1, bytesize);
    RUNLOGF("%p <= exec.AllocMem(0x%x, 0x%x)", ptr, bytesize, attributes);
    return ptr;
}
