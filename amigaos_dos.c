// amigaos_dos.c
#include "amiga39.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// TODO: Close -- Close an open file
LONG Close(BPTR bfile)
{
    RUNLOGF("1 <= dos.Close(0x%x) STUB", bfile);
    return TRUE;
}

// Delay -- Delay a process for a specified time (1/50th sec)
void Delay(int32_t timeout)
{
    RUNLOGF("<= dos.Delay(%d)", timeout);
    SDL_Delay(timeout * 20);        // convert to milliseconds
}

// TODO: IoErr -- Return extra information from the system
LONG IoErr(void)
{
    RUNLOG("0 <= dos.IoErr() STUB");
    return 0;
}

// TODO: LoadSeg -- Scatterload a loadable file into memory
BPTR LoadSeg(STRPTR name)
{
    BPTR res = 0;
    (void)name;
    RUNLOGF("0x%x <= dos.LoadSeg(\"%s\") STUB", res, name);
    return res;
}

// TODO: Lock -- Lock a directory or file
BPTR Lock(STRPTR name, int32_t type)
{
    BPTR res = 0;
    (void)name;
    (void)type;
    RUNLOGF("0x%x <= dos.Lock(\"%s\", 0x%x) STUB", res, name, type);
    return res;
}

// TODO: Open -- Open a file for input or output
BPTR Open(STRPTR name, int32_t accessMode)
{
    BPTR res = 0;
    (void)name;
    (void)accessMode;
    RUNLOGF("0x%x <= dos.Open(\"%s\", 0x%x) STUB", res, name, accessMode);
    return res;
}

// TODO: Read -- Read bytes of data from a file
LONG Read(BPTR file, APTR buffer, int32_t length)
{
    LONG res = 0;
    (void)file;
    (void)buffer;
    (void)length;
    RUNLOGF("0x%x <= dos.Read(0x%x, %p, %d) STUB", res, file, buffer, length);
    return res;
}

// EOF
