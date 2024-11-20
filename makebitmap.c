// fsubs.c
#include "ftale.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

BOOL MakeBitMap(struct BitMap * b, int32_t depth, int32_t width, int32_t height, const char * name)
{
    RUNLOGF("<= MakeBitMap(0x%p, %d, %d, %d, \"%s\")", b, depth, width, height, name);

    if (!b)
        return FALSE;

    InitBitMap(b, depth, width, height, name);

    return TRUE;
}

void UnMakeBitMap(struct BitMap * b)
{
    RUNLOGF("<= UnMakeBitMap(0x%p)", b);

    if (b)
    {
        SDL_FreeSurface(b->Surface);
        b->Surface = NULL;
        b->Depth = 0; /* mark bitmap as empty */
    }
}

// EOF
