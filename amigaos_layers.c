// amigaos_layers.c
#include "amiga39.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// TODO: CreateUpfrontLayer -- Create a new layer on top of existing layers.
struct Layer * CreateUpfrontLayer(struct Layer_Info * li,
                                  struct BitMap *     bm,
                                  int32_t             x0,
                                  int32_t             y0,
                                  int32_t             x1,
                                  int32_t             y1,
                                  int32_t             flags,
                                  struct BitMap *     bm2)
{
    struct Layer * res = NULL;
    (void)li;
    (void)bm;
    (void)x0;
    (void)y0;
    (void)x1;
    (void)y1;
    (void)flags;
    (void)bm2;
    RUNLOGF("%p <= layers.CreateUpfrontLayer(%p, %p, %d, %d, %d, %d, 0x%x, %p) STUB",
            res,
            li,
            bm,
            x0,
            y0,
            x1,
            y1,
            flags,
            bm2);
    return res;
}
