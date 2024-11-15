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

// TODO: DoIO -- perform an I/O command and wait for completion
BYTE DoIO(struct IORequest * ioRequest)
{
    BYTE res = 0;
    (void)ioRequest;
    RUNLOGF("%d <= exec.DoIO(%p)", res, ioRequest);
    return res;
}

// TODO: FindTask -- find a task with the given name or find oneself
struct Task * FindTask(UBYTE * name)
{
    struct Task * res = NULL;
    (void)name;
    RUNLOGF("%p <= exec.FindTask(%p)", res, name);
    return res;
}

// TODO: FreeMem -- deallocate with knowledge
void FreeMem(APTR memoryBlock, uint32_t byteSize)
{
    (void)memoryBlock;
    (void)byteSize;
    RUNLOGF("<= exec.FreeMem(%p, %d) STUB", memoryBlock, byteSize);
}

// TODO: OpenDevice -- gain access to a device
BYTE OpenDevice(char * devName, uint32_t unit, struct IORequest * ioRequest, uint32_t flags)
{
    BYTE res = 0;
    (void)devName;
    (void)unit;
    (void)ioRequest;
    (void)flags;
    RUNLOGF(
        "%d <= exec.OpenDevice(\"%s\", %d, %p, 0x%0x) STUB", res, devName, unit, ioRequest, flags);
    return res;
}

// TODO: OpenLibrary -- gain access to a library
struct Library * OpenLibrary(char * libName, uint32_t version)
{
    struct Library * res = NULL;
    (void)libName;
    (void)version;
    RUNLOGF("%p <= exec.OpenLibrary(\"%s\", %d) STUB", res, libName, version);
    return res;
}

// EOF
