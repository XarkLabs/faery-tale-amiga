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
void Delay( int32_t timeout )
{
    RUNLOGF("<= dos.Delay(%d)", timeout);
    SDL_Delay(timeout * 20); // convert to milliseconds
}
