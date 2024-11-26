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

// FreeMem -- deallocate with knowledge
void FreeMem(APTR memoryBlock, uint32_t byteSize)
{
    (void)byteSize;
    RUNLOGF("<= exec.FreeMem(%p, %d)", memoryBlock, byteSize);
    free(memoryBlock);
}

// Delay -- Delay a process for a specified time (1/50th sec)
void Delay(int32_t timeout)
{
    if (timeout > 50)        // TODO: hack delay time
        timeout = 50;

    while (timeout-- > 0)
    {
        sdl_pump();
        if (cheat2 || sdl_quit || sdl_screenshot)
            break;
        SDL_Delay(20);        // convert to milliseconds
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

// BltBitMap -- Move a rectangular region of bits in a BitMap.
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
    (void)minterm;
    (void)mask;
    (void)tempA;
    LONG res = 0;

    SDL_Rect sr = {xSrc, ySrc, xSize, ySize};
    SDL_Rect dr = {xDest, yDest, xDest + xSize, yDest + ySize};
    sdl_blitsurface8(srcBitMap->Surface, &sr, destBitMap->Surface, &dr);

    return res;
}

// ChangeSprite( vp, s, newdata)
void ChangeSprite(struct ViewPort * vp, uint16_t width, uint16_t height, UBYTE * newData)
{
    RUNLOGF("<= graphics.ChangeSprite(%p, %d, %d, %p)", vp, width, height, newData);
    ASSERT(width == 16);

    if (sdl_cursor_image)
    {
        SDL_FreeSurface(sdl_cursor_image);
        sdl_cursor_image = NULL;
    }
    sdl_cursor_image = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    if (!SDL_LockSurface(sdl_cursor_image))
    {
        uint16_t * sb = (uint16_t *)newData;
        UBYTE *    pb = sdl_cursor_image->pixels;
        //            DPRINT("cursor sprite:\n");
        for (int y = 0; y < 16; y++)
        {
            UBYTE *  pl = pb + (sdl_cursor_image->pitch * y);
            uint32_t m  = 0x8000;
            for (int x = 0; x < 16; x++)
            {
                pl[x] = ((sb[0] & m) ? 1 : 0) + ((sb[1] & m) ? 2 : 0);
                //                    DPRINTF("%c", '0' + pl[x]);
                m >>= 1;
            }
            sb += 2;
            //                DPRINT("\n");
        }
        SDL_UnlockSurface(sdl_cursor_image);
    }

    sdl_update_cursor(vp);
}

// DisownBlitter -- return blitter to free state.
void DisownBlitter(void)
{
}

// FreeColorMap -- Free the ColorMap structure and return memory
void FreeColorMap(struct ColorMap * colorMap)
{
    RUNLOGF("<= graphics.FreeColorMap(%p)", colorMap);
    free(colorMap);
}

// GetColorMap -- allocate and initialize Colormap
struct ColorMap * GetColorMap(int32_t entries)
{
    struct ColorMap * res = NULL;
    (void)entries;
    //    RUNLOGF("%p <= graphics.GetColorMap(%d)", res, entries);
    res = calloc(1, sizeof(struct ColorMap));
    return res;
}


// TODO: InitBitMap -- Initialize bit map structure with input values.
void InitBitMap(struct BitMap * bitMap,
                int32_t         depth,
                int32_t         width,
                int32_t         height,
                const char *    name)
{
    RUNLOGF("<= graphics.InitBitMap(%p, %d, %d, %d, \"%s\")", bitMap, depth, width, height, name);

    if (bitMap->Depth && bitMap->Surface)
    {
        RUNLOGF("InitBitMap: NOTE: freeing existing Surface %s", bitMap->Name);
        SDL_FreeSurface(bitMap->Surface);
    }
    memset(bitMap, 0, sizeof(struct BitMap));

    bitMap->Surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    if (bitMap->Surface)
    {
        bitMap->BytesPerRow = bitMap->Surface->pitch;        //(((width + 15) >> 4) << 1);
        bitMap->Rows        = height;
        bitMap->Flags       = 0;
        bitMap->Depth       = depth;
        bitMap->Name        = name;
    }
}

// Allocate and initialize a font.
struct TextFont * OpenFont(const char * fntPath, const char * pngPath)
{
    struct TextFont * font;

    FILE * f = fopen(fntPath, "rb");
    if (!f)
    {
        RUNLOGF("Unable to open: %s", fntPath);
        return NULL;
    }

    font = calloc(1, sizeof(struct TextFont));

    fread(&(font->LoChar), sizeof(font->LoChar), 1, f);
    fread(&(font->NumGlyphs), sizeof(font->NumGlyphs), 1, f);
    fread(&(font->BaseLine), sizeof(font->BaseLine), 1, f);

    font->Glyphs = calloc(font->NumGlyphs, sizeof(struct GlyphInfo));
    for (uint8_t i = 0; i < font->NumGlyphs; ++i)
    {
        struct GlyphInfo * glyphInfo = &(font->Glyphs[i]);
        fread(&(glyphInfo->LocationStart), sizeof(glyphInfo->LocationStart), 1, f);
        fread(&(glyphInfo->BitLength), sizeof(glyphInfo->BitLength), 1, f);
        fread(&(glyphInfo->Spacing), sizeof(glyphInfo->Spacing), 1, f);
    }

    fclose(f);

    font->Bitmap = IMG_Load(pngPath);
    if (!font->Bitmap)
    {
        RUNLOGF("... failed: %s", SDL_GetError());
        return NULL;
    }

    ASSERT(font->Bitmap->format->format == SDL_PIXELFORMAT_INDEX8);
    if (!SDL_LockSurface(font->Bitmap))
    {
        UBYTE * sp = font->Bitmap->pixels;
        for (int v = 0; v < font->Bitmap->h; v++)
        {
            int     w   = font->Bitmap->w;
            UBYTE * scp = sp;
            while (w--)
            {
                *scp = *scp ? 0xFF : 0x00;
                scp++;
            }
            sp += font->Bitmap->pitch;
        }
    }

    return font;
}

// Deallocate a font.
void FreeFont(struct TextFont * font)
{
    if (font->Bitmap)
        SDL_FreeSurface(font->Bitmap);

    if (font->Glyphs)
        free(font->Glyphs);

    free(font);
}

// TODO: InitRastPort -- Initialize raster port structure
void InitRastPort(struct RastPort * rp)
{
    (void)rp;
    // spammy    RUNLOGF("<= graphics.InitRastPort(%p)", rp);
    memset(rp, 0, sizeof(struct RastPort));
    rp->FgPen    = -1;
    rp->DrawMode = JAM2;
}

void InitVPort(struct ViewPort * vp)
{
    (void)vp;
    RUNLOGF("<= graphics.InitVPort(%p)", vp);
    memset(vp, 0, sizeof(struct ViewPort));
}

void InitView(struct View * view)
{
    (void)view;
    RUNLOGF("<= graphics.InitView(%p)", view);
    memset(view, 0, sizeof(struct View));
}

// LoadRGB4 -- Load RGB color values from table.
void LoadRGB4(struct ViewPort * vp, UWORD * colors, int32_t count)
{
    RUNLOGF("<= graphics.LoadRGB4(%p, %p, %d)", vp, colors, count);
    DPRINT("... [");
    for (int i = 0; i < count && i < 256; i++)
    {
        vp->ColorMap->colors[i] = amiga_color(colors[i]);
        DPRINTF(" %04x", colors[i]);
    }
    DPRINT(" ]\n");
}

// BltBitMap -- Move a rectangular region of bits in a BitMap.
void Move(struct RastPort * rp, int32_t x, int32_t y)
{
    (void)rp;
    (void)x;
    (void)y;
    RUNLOGF("<= graphics.Move(%p, %d, %d)", rp, x, y);
    rp->cp_x = x;
    rp->cp_y = y;
}

// OwnBlitter -- get the blitter for private usage
void OwnBlitter(void)
{
}

// RectFill -- Fill a rectangular region in a RastPort.
void RectFill(struct RastPort * rp, int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax)
{
    RUNLOGF("<= graphics.RectFill(%p, %d, %d, %d, %d)", rp, xMin, yMin, xMax, yMax);
    SDL_Rect dr = {xMin, yMin, xMax - xMin + 1, yMax - yMin + 1};
    SDL_FillRect(rp->BitMap->Surface, &dr, rp->FgPen);
}

// ScrollRaster -- Push bits in rectangle in raster around by dx,dy towards 0,0 inside
// rectangle.
void ScrollRaster(struct RastPort * rp,
                  int32_t           dx,
                  int32_t           dy,
                  int32_t           xMin,
                  int32_t           yMin,
                  int32_t           xMax,
                  int32_t           yMax)
{
    RUNLOGF(
        "<= graphics.ScrollRaster(%p, %d, %d, %d, %d, %d, %d)", rp, dx, dy, xMin, yMin, xMax, yMax);

    ASSERT(dy > 0);

    SDL_Surface * s = rp->BitMap->Surface;
    if (xMax >= s->w)
    {
        xMax = s->w - 1;
    }
    if (yMax >= s->h)
    {
        yMax = s->h - 1;
    }

    if (!SDL_LockSurface(s))
    {
        int16_t w  = xMax - xMin + 1;
        UBYTE * dp = (UBYTE *)s->pixels + (yMin * s->pitch) + xMin;
        UBYTE * sp = dp + (dy * s->pitch) + dx;
        for (int16_t v = yMin; v <= yMax; v++)
        {
            if ((v + dy) <= yMax)
            {
                memmove(dp, sp, w);
            }
            else
            {
                memset(dp, rp->BgPen, w);
            }
            dp += s->pitch;
            sp += s->pitch;
        }
    }
    SDL_UnlockSurface(s);
}

// SetAPen -- Set the primary pen for a RastPort.
void SetAPen(struct RastPort * rp, uint32_t pen)
{
    rp->FgPen = pen;
}

// SetBPen -- Set the secondary pen for a RastPort.
void SetBPen(struct RastPort * rp, uint32_t pen)
{
    rp->BgPen = pen;
}

// SetDrMd -- Set drawing mode for a RastPort
void SetDrMd(struct RastPort * rp, uint32_t drawMode)
{
    rp->DrawMode = drawMode;
}

// Set the text font and attributes in a RastPort.
void SetFont(struct RastPort * rp, struct TextFont * textFont)
{
    rp->Font = textFont;
}

// SetRast - Set an entire drawing area to a specified color.
void SetRast(struct RastPort * rp, uint32_t pen)
{
    (void)rp;
    (void)pen;
    SDL_FillRect(rp->BitMap->Surface, NULL, pen);
}

// TODO: SetRGB4 -- Set one color register for this viewport.
void SetRGB4(struct ViewPort * vp, int32_t index, uint32_t red, uint32_t green, uint32_t blue)
{
    uint16_t ac                 = ((red & 0xf) << 8) | ((green & 0xf) << 4) | (blue & 0xf);
    vp->ColorMap->colors[index] = amiga_color(ac);
}

// Text -- Write text characters (no formatting).
LONG Text(struct RastPort * rp, STRPTR string, uint32_t count)
{
    ULONG res = 0;

    uint32_t len = strlen(string);
    if (len > count)
    {
        len = count;
    }
    RUNLOGF("... Text(%d,%d, len=%d, pen=%d/%d %s]",
            rp->cp_x,
            rp->cp_y,
            len,
            rp->FgPen,
            rp->BgPen,
            c_string(string, count < 80 ? count : 80));
    for (uint32_t x = 0; x < len && string[x]; x++)
    {
        if (string[x] >= rp->Font->LoChar && string[x] < rp->Font->LoChar + rp->Font->NumGlyphs)
        {
            uint8_t            glyphIndex = string[x] - rp->Font->LoChar;
            struct GlyphInfo * glyph      = &(rp->Font->Glyphs[glyphIndex]);
            SDL_Rect           dr = {rp->cp_x, rp->cp_y - rp->Font->BaseLine , glyph->BitLength, rp->Font->Bitmap->h};  // Xark: Draw using y+baseline as origin
            SDL_Rect sr = {glyph->LocationStart, 0, glyph->BitLength, rp->Font->Bitmap->h};
            SDL_FillRect(rp->BitMap->Surface, &dr, rp->BgPen);
            sdl_blitsurface8_mask(rp->Font->Bitmap, &sr, rp->BitMap->Surface, &dr, rp->FgPen);
            rp->cp_x += glyph->Spacing;
        }
    }

    return res;
}

// TODO: WaitBlit -- Wait for the blitter to be finished before proceeding
void WaitBlit(void)
{
}

// EOF
