// amigaos_graphics.c
#include "amiga39.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// planeptr = AllocRaster( width, height )
PLANEPTR AllocRaster(uint32_t width, uint32_t height)
{
    void * ptr = calloc(1, ((width + 15) / 16) * height);
    RUNLOGF("%p <= graphics.AllocRaster(%d, %d)", ptr, width, height);
    return ptr;
}

// error = AreaDraw( rp,  x,     y)
int32_t AreaDraw(struct RastPort * rp, int32_t x, int32_t y)
{
    // TODO: AreaDraw
    RUNLOGF("0x%x <= graphics.AreaDraw(%p, %d, %d) STUB", 0, rp, x, y);
    return 0;
}

// error = AreaMove( rp,  x,     y)
int32_t AreaMove(struct RastPort * rp, int32_t x, int32_t y)
{
    // TODO: AreaMove
    RUNLOGF("0x%x <= graphics.AreaMove(%p, %d, %d) STUB", 0, rp, x, y);
    return 0;
}

// error = AreaEnd( rp )
int32_t AreaEnd(struct RastPort * rp)
{
    // TODO: AreaEnd
    RUNLOGF("0x%x <= graphics.AreaEnd(%p) STUB", 0, rp);
    return 0;
}

// planecnt = BltBitMap(SrcBitMap, SrcX, SrcY, DstBitMap, DstX, DstY, SizeX, SizeY, Minterm, Mask,
// TempA)
LONG BltBitMap(struct BitMap * srcBitMap,
               int32_t         xSrc,
               int32_t         ySrc,
               struct BitMap * destBitMap,
               int32_t         xDest,
               int32_t         yDest,
               int32_t         xSize,
               int32_t         ySize,
               uint32_t        minterm,
               uint32_t        mask,
               PLANEPTR        tempA)
{
    // TODO: BltBitMap
    LONG res = 0;
    RUNLOGF("%d <= graphics.BltBitMap(%p, %d, %d, %p, %d, %d, %d, %d, 0x%x, 0x%x, %p) STUB",
            res,
            srcBitMap,
            xSrc,
            ySrc,
            destBitMap,
            xDest,
            yDest,
            xSize,
            ySize,
            minterm,
            mask,
            tempA);
    return res;
}

// ChangeSprite( vp, s, newdata)
void ChangeSprite(struct ViewPort * vp, struct SimpleSprite * sprite, PLANEPTR newData)
{
    RUNLOGF("<= graphics.ChangeSprite(%p, %p, %p) STUB", vp, sprite, newData);
}
