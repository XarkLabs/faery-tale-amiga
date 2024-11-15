// amigaos_graphics.c
#include "amiga39.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// AllocRaster -- Allocate space for a bitplane.
PLANEPTR AllocRaster(uint32_t width, uint32_t height)
{
    void * res = NULL;
    (void)width;
    (void)height;
    RUNLOGF("%p <= graphics.AllocRaster(%d, %d)", res, width, height);
    return res;
}

// TODO: AreaDraw -- Add a point to a list of end points for areafill.
int32_t AreaDraw(struct RastPort * rp, int32_t x, int32_t y)
{
    (void)rp;
    (void)x;
    (void)y;
    RUNLOGF("0x%x <= graphics.AreaDraw(%p, %d, %d) STUB", 0, rp, x, y);
    return 0;
}

// TODO: AreaMove -- Define a new starting point for a new
int32_t AreaMove(struct RastPort * rp, int32_t x, int32_t y)
{
    (void)rp;
    (void)x;
    (void)y;
    RUNLOGF("0x%x <= graphics.AreaMove(%p, %d, %d) STUB", 0, rp, x, y);
    return 0;
}

// TODO: AreaEnd -- Process table of vectors and ellipses and produce areafill.
int32_t AreaEnd(struct RastPort * rp)
{
    (void)rp;
    RUNLOGF("0x%x <= graphics.AreaEnd(%p) STUB", 0, rp);
    return 0;
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
               PLANEPTR        tempA)
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

// TODO: ChangeSprite( vp, s, newdata)
void ChangeSprite(struct ViewPort * vp, struct SimpleSprite * sprite, PLANEPTR newData)
{
    (void)vp;
    (void)sprite;
    (void)newData;
    RUNLOGF("<= graphics.ChangeSprite(%p, %p, %p) STUB", vp, sprite, newData);
}

// TODO: DisownBlitter -- return blitter to free state.
void DisownBlitter(void)
{
    RUNLOG("<= graphics.DisownBlitter() STUB");
}

// TODO: FreeColorMap -- Free the ColorMap structure and return memory
void FreeColorMap(struct ColorMap * colorMap)
{
    RUNLOGF("<= graphics.FreeColorMap(%p) STUB", colorMap);
}

// TODO: FreeCprList -- deallocate hardware copper list
void FreeCprList(struct cprlist * cprList)
{
    (void)cprList;
    RUNLOGF("<= graphics.FreeCprList(%p) STUB", cprList);
}


// TODO: FreeRaster -- Release an allocated area to the system free memory pool
void FreeRaster(PLANEPTR p, uint32_t width, uint32_t height)
{
    (void)p;
    (void)width;
    (void)height;
    RUNLOGF("<= graphics.FreeRaster(%p, %d, %d) STUB", p, width, height);
}

// TODO: FreeSprite -- Return sprite for use by others and virtual
void FreeSprite(int32_t num)
{
    (void)num;
    RUNLOGF("<= graphics.FreeSprite(%d) STUB", num);
}

// TODO: FreeVPortCopLists -- deallocate all intermediate copper lists and their headers from a
// viewport
void FreeVPortCopLists(struct ViewPort * vp)
{
    (void)vp;
    RUNLOGF("<= graphics.FreeVPortCopLists(%p) STUB", vp);
}

// TODO: GetColorMap -- allocate and initialize Colormap
struct ColorMap * GetColorMap(int32_t entries)
{
    struct ColorMap * res = NULL;
    (void)entries;
    RUNLOGF("%p <= graphics.AreaEnd(%d) STUB", res, entries);
    return res;
}

// TODO: GetSprite -- Attempt to get a sprite for the simple sprite manager.
WORD GetSprite(struct SimpleSprite * sprite, int32_t num)
{
    WORD res = -1;
    (void)sprite;
    (void)num;
    RUNLOGF("%d <= graphics.AreaEnd(%p, %d) STUB", res, sprite, num);
    return res;
}

// TODO: InitArea -- Initialize vector collection matrix
void InitArea(struct AreaInfo * areaInfo, APTR vectorBuffer, int32_t maxVectors)
{
    (void)areaInfo;
    (void)vectorBuffer;
    (void)maxVectors;
    RUNLOGF("<= graphics.InitArea(%p, %p, %d) STUB", areaInfo, vectorBuffer, maxVectors);
}

// TODO: InitBitMap -- Initialize bit map structure with input values.
void InitBitMap(struct BitMap * bitMap, int32_t depth, int32_t width, int32_t height)
{
    (void)bitMap;
    (void)depth;
    (void)width;
    (void)height;
    RUNLOGF("<= graphics.InitBitMap(%p, %d, %d, %d) STUB", bitMap, depth, width, height);
}

// TODO: InitRastPort -- Initialize raster port structure
void InitRastPort(struct RastPort * rp)
{
    (void)rp;
    RUNLOGF("<= graphics.InitRastPort(%p) STUB", rp);
}

// TODO: InitTmpRas -- Initialize area of local memory for usage by
struct TmpRas * InitTmpRas(struct TmpRas * tmpRas, PLANEPTR buffer, int32_t size)
{
    struct TmpRas * res = NULL;
    (void)tmpRas;
    (void)buffer;
    (void)size;
    RUNLOGF("%p <= graphics.InitTmpRas(%p, %p, %d) STUB", res, tmpRas, buffer, size);
    return res;
}

// TODO: InitVPort - Initialize ViewPort structure.
void InitVPort(struct ViewPort * vp)
{
    (void)vp;
    RUNLOGF("<= graphics.InitVPort(%p) STUB", vp);
}

// TODO: InitView - Initialize View structure.
void InitView(struct View * view)
{
    (void)view;
    RUNLOGF("<= graphics.InitView(%p) STUB", view);
}

// TODO: LoadRGB4 -- Load RGB color values from table.
void LoadRGB4(struct ViewPort * vp, UWORD * colors, int32_t count)
{
    (void)vp;
    (void)colors;
    (void)count;
    RUNLOGF("<= graphics.LoadRGB4(%p, %p, %d) STUB", vp, colors, count);
}

// TODO: LoadView -- Use a (possibly freshly created) coprocessor instruction list to create the
// current display.
void LoadView(struct View * view)
{
    (void)view;
    RUNLOGF("<= graphics.LoadView(%p) STUB", view);
}

// TODO: MakeVPort -- generate display copper list for a viewport.
ULONG MakeVPort(struct View * view, struct ViewPort * vp)
{
    ULONG res = 0;
    (void)view;
    (void)vp;
    RUNLOGF("%d <= graphics.MakeVPort(%p, %p) STUB", res, view, vp);
    return res;
}

// TODO: BltBitMap -- Move a rectangular region of bits in a BitMap.
void Move(struct RastPort * rp, int32_t x, int32_t y)
{
    (void)rp;
    (void)x;
    (void)y;
    RUNLOGF("<= graphics.Move(%p, %d, %d) STUB", rp, x, y);
}

// TODO: MrgCop -- Merge together coprocessor instructions.
ULONG MrgCop(struct View * view)
{
    ULONG res = 0;
    (void)view;
    RUNLOGF("%d <= graphics.MrgCop(%p) STUB", res, view);
    return res;
}

// TODO; OpenFont -- Get a pointer to a system font.
struct TextFont * OpenFont(struct TextAttr * textAttr)
{
    struct TextFont * res = NULL;
    (void)textAttr;
    RUNLOGF("%p <= graphics.OpenFont(%p) STUB", res, textAttr);
    return res;
}

// TODO: OwnBlitter -- get the blitter for private usage
void OwnBlitter(void)
{
    RUNLOG("<= graphics.OwnBlitter() STUB");
}

// TODO: RectFill -- Fill a rectangular region in a RastPort.
void RectFill(struct RastPort * rp, int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax)
{
    (void)rp;
    (void)xMin;
    (void)yMin;
    (void)xMax;
    (void)yMax;
    RUNLOGF("<= graphics.RectFill(%p, %d, %d, %d, %d) STUB", rp, xMin, yMin, xMax, yMax);
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
    RUNLOGF("<= graphics.SetAPen(%p, %d) STUB", rp, pen);
}

// TODO: SetBPen -- Set the secondary pen for a RastPort.
void SetBPen(struct RastPort * rp, uint32_t pen)
{
    (void)rp;
    (void)pen;
    RUNLOGF("<= graphics.SetBPen(%p, %d) STUB", rp, pen);
}

// TODO: SetDrMd -- Set drawing mode for a RastPort
void SetDrMd(struct RastPort * rp, uint32_t drawMode)
{
    (void)rp;
    (void)drawMode;
    RUNLOGF("<= graphics.SetDrMd(%p, %d) STUB", rp, drawMode);
}

// TODO: SetRast - Set an entire drawing area to a specified color.
void SetRast(struct RastPort * rp, uint32_t pen)
{
    (void)rp;
    (void)pen;
    RUNLOGF("<= graphics.SetRast(%p, %d) STUB", rp, pen);
}

// TODO: SetFont -- Set the text font and attributes in a RastPort.
LONG SetFont(struct RastPort * rp, struct TextFont * textFont)
{
    ULONG res = 0;
    (void)rp;
    (void)textFont;
    RUNLOGF("%d <= graphics.SetFont(%p, %p) STUB", res, rp, textFont);
    return res;
}

// TODO: SetRGB4 -- Set one color register for this viewport.
void SetRGB4(struct ViewPort * vp, int32_t index, uint32_t red, uint32_t green, uint32_t blue)
{
    (void)index;
    (void)red;
    (void)green;
    (void)blue;
    RUNLOGF("<= graphics.SetRGB4(%p, %d, %d, %d, %d) STUB", vp, index, red, green, blue);
}

// Text -- Write text characters (no formatting).
LONG Text(struct RastPort * rp, STRPTR string, uint32_t count)
{
    ULONG res = 0;
    (void)rp;
    (void)string;
    (void)count;
    RUNLOGF("%d <= graphics.Text(%p, \"%*s\", %d) STUB",
            res,
            rp,
            count < 100 ? count : 100,
            string,
            count);
    return res;
}

// TODO: WaitBOVP -- Wait till vertical beam reached bottom of this viewport.
void WaitBOVP(struct ViewPort * vp)
{
    (void)vp;
    RUNLOGF("<= graphics.WaitBOVP(%p) STUB", vp);
}

// TODO: WaitBlit -- Wait for the blitter to be finished before proceeding
void WaitBlit(void)
{
    RUNLOG("<= graphics.WaitBlit() STUB");
}

// EOF
