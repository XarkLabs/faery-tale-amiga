// amigaos_graphics.c
#include "amigaos.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "ftale.h"

// AllocMem -- allocate memory given certain requirements
APTR AllocMem(uint32_t bytesize, uint32_t attributes)
{
    (void)attributes;
    void * ptr = malloc(bytesize);
    if (ptr)
    {
        memset(ptr, 0, bytesize);
    }
    RUNLOGF("%p <= exec.AllocMem(%d, 0x%x)", ptr, bytesize, attributes);
    return ptr;
}

// TODO: FreeMem -- deallocate with knowledge
void FreeMem(APTR memoryBlock, uint32_t byteSize)
{
    (void)memoryBlock;
    (void)byteSize;
    RUNLOGF("<= exec.FreeMem(%p, %d) STUB", memoryBlock, byteSize);
}

// Delay -- Delay a process for a specified time (1/50th sec)
void Delay(int32_t timeout)
{
    (void)timeout;
    // spammy    RUNLOGF("<= dos.Delay(%d)", timeout);

    while (timeout-- > 0)
    {
        sdl_pump();
        SDL_Delay(1 /* 20 */);        // convert to milliseconds // FIXME: fast time
    }
}

// IoErr -- Return extra information from the system
LONG IoErr(void)
{
    LONG res = errno;
    RUNLOGF("%d <= dos.IoErr() [%s]", res, strerror(res));
    return res;
}

// AllocRaster -- Allocate space for a bitplane.
UBYTE * AllocRaster(uint32_t width, uint32_t height)
{
    void * res = NULL;
    (void)width;
    (void)height;
    int32_t bytes = (((width + 15) >> 4) << 1) * height;
    res           = malloc(bytes);
    if (res)
    {
        memset(res, 0, bytes);
    }
    // spammy    RUNLOGF("%p <= graphics.AllocRaster(%d, %d)", res, width, height);
    return res;
}

// TODO: BltBitMap -- Move a rectangular region of bits in a BitMap.
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
               UBYTE *         tempA)
{
    LONG res = 0;
    (void)srcBitMap;
    (void)xSrc;
    (void)ySrc;
    (void)destBitMap;
    (void)xDest;
    (void)yDest;
    (void)xSize;
    (void)ySize;
    (void)minterm;
    (void)mask;
    (void)tempA;

    // RUNLOGF("%d <= graphics.BltBitMap(%p, %d, %d, %p, %d, %d, %d, %d, 0x%x, 0x%x, %p) STUB",
    //         res,
    //         srcBitMap,
    //         xSrc,
    //         ySrc,
    //         destBitMap,
    //         xDest,
    //         yDest,
    //         xSize,
    //         ySize,
    //         minterm,
    //         mask,
    //         tempA);

    SDL_Rect sr = {xSrc, ySrc, xSize, ySize};
    SDL_Rect dr = {xDest, yDest, 0x7fff, 0x7fff};
    SDL_BlitSurface(srcBitMap->Surface, &sr, destBitMap->Surface, &dr);

    return res;
}

// TODO: ChangeSprite( vp, s, newdata)
void ChangeSprite(struct ViewPort * vp, uint16_t width, uint16_t height, UBYTE * newData)
{
    RUNLOGF("<= graphics.ChangeSprite(%p, %d, %d, %p)", vp, width, height, newData);
    ASSERT(width == 16);
    if (!sdl_cursor_image)
    {
        sdl_cursor_image = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    }
        
    if (!SDL_LockSurface(sdl_cursor_image))
    {
        uint16_t * sb = (uint16_t *)newData;
        UBYTE *    pb = sdl_cursor_image->pixels;
        DPRINT("cursor sprite:\n");
        for (int y = 0; y < 16; y++)
        {
            UBYTE *  pl = pb + (sdl_cursor_image->pitch * y);
            uint32_t m  = 0x8000;
            for (int x = 0; x < 16; x++)
            {
                pl[x] = ((sb[0] & m) ? 1 : 0) + ((sb[1] & m) ? 2 : 0);
                DPRINTF("%c", '0' + pl[x]);
                m >>= 1;
            }
            sb += 2;
            DPRINT("\n");
        }
        SDL_UnlockSurface(sdl_cursor_image);
    }

    sdl_update_cursor(vp);
}

// TODO: DisownBlitter -- return blitter to free state.
void DisownBlitter(void)
{
    // spammy    RUNLOG("<= graphics.DisownBlitter() STUB");
}

// TODO: FreeColorMap -- Free the ColorMap structure and return memory
void FreeColorMap(struct ColorMap * colorMap)
{
    RUNLOGF("<= graphics.FreeColorMap(%p)", colorMap);
    free(colorMap);
}

// // TODO: FreeCprList -- deallocate hardware copper list
// void FreeCprList(struct cprlist * cprList)
// {
//     (void)cprList;
//     RUNLOGF("<= graphics.FreeCprList(%p) STUB", cprList);
// }
//

// TODO: FreeRaster -- Release an allocated area to the system free memory pool
// void FreeRaster(UBYTE * p, uint32_t width, uint32_t height)
// {
//     (void)p;
//     (void)width;
//     (void)height;
//     RUNLOGF("<= graphics.FreeRaster(%p, %d, %d) STUB", p, width, height);
// }

// TODO: FreeSprite -- Return sprite for use by others and virtual
// void FreeSprite(int32_t num)
// {
//     (void)num;
//     // spammy    RUNLOGF("<= graphics.FreeSprite(%d) STUB", num);
// }

// // TODO: FreeVPortCopLists -- deallocate all intermediate copper lists and their headers from a
// // viewport
// void FreeVPortCopLists(struct ViewPort * vp)
// {
//     (void)vp;
//     RUNLOGF("<= graphics.FreeVPortCopLists(%p) STUB", vp);
// }

// TODO: GetColorMap -- allocate and initialize Colormap
struct ColorMap * GetColorMap(int32_t entries)
{
    struct ColorMap * res = NULL;
    (void)entries;
    //    RUNLOGF("%p <= graphics.GetColorMap(%d) STUB", res, entries);
    res = calloc(1, sizeof(struct ColorMap));
    return res;
}

// // TODO: GetSprite -- Attempt to get a sprite for the simple sprite manager.
// WORD GetSprite(struct SimpleSprite * sprite, int32_t num)
// {
//     WORD res = -1;
//     (void)sprite;
//     (void)num;
//     RUNLOGF("%d <= graphics.AreaEnd(%p, %d) STUB", res, sprite, num);
//     return res;
// }

// // TODO: InitArea -- Initialize vector collection matrix
// void InitArea(struct AreaInfo * areaInfo, APTR vectorBuffer, int32_t maxVectors)
// {
//     (void)areaInfo;
//     (void)vectorBuffer;
//     (void)maxVectors;
//     RUNLOGF("<= graphics.InitArea(%p, %p, %d) STUB", areaInfo, vectorBuffer, maxVectors);
// }

// TODO: InitBitMap -- Initialize bit map structure with input values.
void InitBitMap(struct BitMap * bitMap, int32_t depth, int32_t width, int32_t height)
{
    (void)bitMap;
    (void)depth;
    (void)width;
    (void)height;
    // spammy    RUNLOGF("<= graphics.InitBitMap(%p, %d, %d, %d)", bitMap, depth, width, height);
    memset(bitMap, 0, sizeof(struct BitMap));

    bitMap->Surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    if (bitMap->Surface)
    {
        bitMap->BytesPerRow = bitMap->Surface->pitch;        //(((width + 15) >> 4) << 1);
        bitMap->Rows        = height;
        bitMap->Flags       = 0;
        bitMap->Depth       = depth;
    }
}

// TODO: InitRastPort -- Initialize raster port structure
void InitRastPort(struct RastPort * rp)
{
    (void)rp;
    // spammy    RUNLOGF("<= graphics.InitRastPort(%p) STUB", rp);
    memset(rp, 0, sizeof(struct RastPort));
    // rp->Mask     = -1;
    rp->FgPen = -1;
    // rp->LinePtrn = -1;
    // rp->DrawMode = JAM2;
    //    rp->Font = TOPAZ;
}

// // TODO: InitTmpRas -- Initialize area of local memory for usage by
// struct TmpRas * InitTmpRas(struct TmpRas * tmpRas, UBYTE * buffer, int32_t size)
// {
//     struct TmpRas * res = NULL;
//     (void)tmpRas;
//     (void)buffer;
//     (void)size;
//     RUNLOGF("%p <= graphics.InitTmpRas(%p, %p, %d) STUB", res, tmpRas, buffer, size);
//     return res;
// }

void InitVPort(struct ViewPort * vp)
{
    (void)vp;
    RUNLOGF("<= graphics.InitVPort(%p) STUB", vp);
    memset(vp, 0, sizeof(struct ViewPort));
}

void InitView(struct View * view)
{
    (void)view;
    RUNLOGF("<= graphics.InitView(%p) STUB", view);
    memset(view, 0, sizeof(struct View));
}

// TODO: LoadRGB4 -- Load RGB color values from table.
void LoadRGB4(struct ViewPort * vp, UWORD * colors, int32_t count)
{
    (void)vp;
    (void)colors;
    (void)count;
    RUNLOGF("<= graphics.LoadRGB4(%p, %p, %d)", vp, colors, count);
    static SDL_Color sdl_colors[256];
    for (int i = 0; i < count && i < 256; i++)
    {
        sdl_colors[i] = amiga_color(colors[i]);
        RUNLOGF("... [#%2d %02x%02x%02x%02x = %04x",
                i,
                sdl_colors[i].r,
                sdl_colors[i].g,
                sdl_colors[i].b,
                sdl_colors[i].a,
                colors[i]);
    }
    SDL_SetPaletteColors(vp->RasInfo->BitMap->Surface->format->palette, sdl_colors, 0, count);
}

// // TODO: LoadView -- Use a (possibly freshly created) coprocessor instruction list to create the
// // current display.
// void LoadView(struct View * view)
// {
//     (void)view;
//     //    RUNLOGF("<= graphics.LoadView(%p) STUB", view);
// }

// // TODO: MakeVPort -- generate display copper list for a viewport.
// ULONG MakeVPort(struct View * view, struct ViewPort * vp)
// {
//     ULONG res = 0;
//     (void)view;
//     (void)vp;
//     //    RUNLOGF("%d <= graphics.MakeVPort(%p, %p) STUB", res, view, vp);
//     return res;
// }

// TODO: BltBitMap -- Move a rectangular region of bits in a BitMap.
void Move(struct RastPort * rp, int32_t x, int32_t y)
{
    (void)rp;
    (void)x;
    (void)y;
    RUNLOGF("<= graphics.Move(%p, %d, %d)", rp, x, y);
    rp->cp_x = x;
    rp->cp_y = y;
}

// // TODO: MrgCop -- Merge together coprocessor instructions.
// ULONG MrgCop(struct View * view)
// {
//     ULONG res = 0;
//     (void)view;
//     //    RUNLOGF("%d <= graphics.MrgCop(%p) STUB", res, view);
//     return res;
// }

// // TODO; OpenFont -- Get a pointer to a system font.
// struct TextFont * OpenFont(struct TextAttr * textAttr)
// {
//     struct TextFont * res = NULL;
//     (void)textAttr;
//     RUNLOGF("%p <= graphics.OpenFont(%p) STUB", res, textAttr);
//     return res;
// }

// TODO: OwnBlitter -- get the blitter for private usage
void OwnBlitter(void)
{
    // spammy    RUNLOG("<= graphics.OwnBlitter() STUB");
}

// TODO: RectFill -- Fill a rectangular region in a RastPort.
void RectFill(struct RastPort * rp, int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax)
{
    (void)rp;
    (void)xMin;
    (void)yMin;
    (void)xMax;
    (void)yMax;
    RUNLOGF("<= graphics.RectFill(%p, %d, %d, %d, %d)", rp, xMin, yMin, xMax, yMax);
    SDL_Rect dr = {xMin, yMin, xMax - xMin, yMax - yMin};
    SDL_FillRect(rp->BitMap->Surface, &dr, rp->FgPen);
}

// TODO: ScrollRaster -- Push bits in rectangle in raster around by dx,dy towards 0,0 inside
// rectangle.
void ScrollRaster(struct RastPort * rp,
                  int32_t           dx,
                  int32_t           dy,
                  int32_t           xMin,
                  int32_t           yMin,
                  int32_t           xMax,
                  int32_t           yMax)
{
    (void)rp;
    (void)dx;
    (void)dy;
    (void)xMin;
    (void)yMin;
    (void)xMax;
    (void)yMax;
    RUNLOGF("<= graphics.ScrollRaster(%p, %d, %d, %d, %d, %d, %d) STUB",
            rp,
            dx,
            dy,
            xMin,
            yMin,
            xMax,
            yMax);
}

// TODO: SetAPen -- Set the primary pen for a RastPort.
void SetAPen(struct RastPort * rp, uint32_t pen)
{
    (void)rp;
    (void)pen;
    // spammy    RUNLOGF("<= graphics.SetAPen(%p, %d) STUB", rp, pen);
    rp->FgPen = pen;
}

// TODO: SetBPen -- Set the secondary pen for a RastPort.
void SetBPen(struct RastPort * rp, uint32_t pen)
{
    (void)rp;
    (void)pen;
    // spammy    RUNLOGF("<= graphics.SetBPen(%p, %d) STUB", rp, pen);
    rp->BgPen = pen;
}

// TODO: SetDrMd -- Set drawing mode for a RastPort
void SetDrMd(struct RastPort * rp, uint32_t drawMode)
{
    (void)rp;
    (void)drawMode;
    // spammy    RUNLOGF("<= graphics.SetDrMd(%p, %d) STUB", rp, drawMode);
    rp->DrawMode = drawMode;
}

// TODO: SetFont -- Set the text font and attributes in a RastPort.
LONG SetFont(struct RastPort * rp, struct TextFont * textFont)
{
    ULONG res = 0;
    (void)rp;
    (void)textFont;
    RUNLOGF("%d <= graphics.SetFont(%p, %p) TEMP", res, rp, textFont);
    return res;
}

// TODO: SetRast - Set an entire drawing area to a specified color.
void SetRast(struct RastPort * rp, uint32_t pen)
{
    (void)rp;
    (void)pen;
    RUNLOGF("<= graphics.SetRast(%p, %d)", rp, pen);
    SDL_FillRect(rp->BitMap->Surface, NULL, pen);
}

// TODO: SetRGB4 -- Set one color register for this viewport.
void SetRGB4(struct ViewPort * vp, int32_t index, uint32_t red, uint32_t green, uint32_t blue)
{
    (void)index;
    (void)red;
    (void)green;
    (void)blue;

    if (vp->RasInfo->BitMap->Surface && vp->RasInfo->BitMap->Surface->format &&
        vp->RasInfo->BitMap->Surface->format->palette)
    {
        static SDL_Color sdl_color;
        sdl_color.r = ((red & 0xf00) >> 4) | ((red & 0xf00) >> 8);
        sdl_color.g = ((green & 0xf0) >> 0) | ((green & 0xf0) >> 4);
        sdl_color.b = ((blue & 0xf) << 4) | ((blue & 0xf) << 0);
        sdl_color.a = 0xff;
        RUNLOGF("SetRGB4 -> [#%2d %02x%02x%02x%02x = %1x%1x%1x]",
                index,
                sdl_color.r,
                sdl_color.g,
                sdl_color.b,
                sdl_color.a,
                red,
                green,
                blue);
        SDL_SetPaletteColors(vp->RasInfo->BitMap->Surface->format->palette, &sdl_color, index, 1);
    }
    else
    {
        RUNLOGF("SetRGB4 colors %d NOT set", index);
    }
}

// Text -- Write text characters (no formatting).
LONG Text(struct RastPort * rp, STRPTR string, uint32_t count)
{
    ULONG res = 0;
    (void)rp;
    (void)string;
    (void)count;
    RUNLOGF("%d <= graphics.Text(%p, %s, %d) STUB", res, rp, c_string(string, count), count);

    uint32_t len = strlen(string);
    if (len > count)
    {
        len = count;
    }
    SDL_Rect dr = {rp->cp_x, rp->cp_y, len * 9, 11};
    RUNLOGF("... [text rect %d,%d - %d,%d, pen=%d]", rp->cp_x, rp->cp_y, len * 9, 11, rp->FgPen);
    SDL_FillRect(rp->BitMap->Surface, &dr, rp->FgPen);        // TODO: Text render

    return res;
}

// // TODO: WaitBOVP -- Wait till vertical beam reached bottom of this viewport.
// void WaitBOVP(struct ViewPort * vp)
// {
//     (void)vp;
//     //    RUNLOGF("<= graphics.WaitBOVP(%p) STUB", vp);
// }

// TODO: WaitBlit -- Wait for the blitter to be finished before proceeding
void WaitBlit(void)
{
    // spammy    RUNLOG("<= graphics.WaitBlit() STUB");
}

// EOF
