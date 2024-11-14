// amigaos_exec.c
#include "amiga39.h"

#include <stdlib.h>
#include <stdio.h>

// memoryBlock = AllocMem(byteSize, attributes)
APTR AllocMem(uint32_t bytesize, uint32_t attributes)
{
    void *ptr = calloc(1, bytesize);
    RUNLOGF("%p <= exec.AllocMem(%d, 0x%x)", ptr, bytesize, attributes);
    return ptr;
}

// size = AvailMem(requirements)
uint32_t AvailMem(uint32_t requirements)
{
    uint32_t res = 256 * 1024;  // TODO: always 256K available...
    RUNLOGF("%u <= exec.AvailMem(0x%x)", res, requirements);
    return res;
}
