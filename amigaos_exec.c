// amigaos_exec.c
#include "amiga39.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// AllocMem -- allocate memory given certain requirements
APTR AllocMem(uint32_t bytesize, uint32_t attributes)
{
    void * ptr = calloc(1, bytesize);
    RUNLOGF("%p <= exec.AllocMem(%d, 0x%x)", ptr, bytesize, attributes);
    return ptr;
}

// AvailMem -- memory available given certain requirements
uint32_t AvailMem(uint32_t requirements)
{
    uint32_t res = 256 * 1024;        // TODO: always 256K available...
    RUNLOGF("%u <= exec.AvailMem(0x%x)", res, requirements);
    return res;
}

// CloseDevice -- conclude access to a device
void CloseDevice(struct IORequest * ioRequest)
{
    (void)ioRequest;
    RUNLOGF("<= exec.CloseDevice(%p)", ioRequest);
}

// CloseFont -- Release a pointer to a system font.
void CloseFont(struct TextFont * textFont)
{
    (void)textFont;
    RUNLOGF("<= exec.CloseFont(%p)", textFont);
}

// CloseLibrary -- conclude access to a library
void CloseLibrary(struct Library * library)
{
    (void)library;
    RUNLOGF("<= exec.CloseLibrary(%p)", library);
}
