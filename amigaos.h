// Xark - Extremely cut down functions needed from Amiga OS

#if !defined(AMIGAOS_H)
#define AMIGAOS_H

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>

#define FTA_NEXGEN 1        // always defined

#define FTA_LOG  1        // log messages
#define SAVE_RAW 0        // save assets

extern FILE * logfilep;

#if defined(FTA_LOG)
#define RUNLOG(msg)                                                                                \
    do                                                                                             \
    {                                                                                              \
        fprintf(logfilep, "%s\n", msg);                                                            \
        fprintf(stdout, "%s\n", msg);                                                              \
        fflush(logfilep);                                                                          \
    } while (0)
#define RUNLOGF(fmtmsg, ...)                                                                       \
    do                                                                                             \
    {                                                                                              \
        fprintf(logfilep, fmtmsg "\n", ##__VA_ARGS__);                                             \
        fprintf(stdout, fmtmsg "\n", ##__VA_ARGS__);                                               \
        fflush(logfilep);                                                                          \
    } while (0)
#else
#define RUNLOG()  (void)
#define RUNLOGF() (void)
#endif

#define DPRINT(msg)                                                                                \
    do                                                                                             \
    {                                                                                              \
        fprintf(logfilep, "%s", msg);                                                              \
        fprintf(stdout, "%s", msg);                                                                \
    } while (0)

#define DPRINTF(fmtmsg, ...)                                                                       \
    do                                                                                             \
    {                                                                                              \
        fprintf(logfilep, fmtmsg, ##__VA_ARGS__);                                                  \
        fprintf(stdout, fmtmsg, ##__VA_ARGS__);                                                    \
    } while (0)

// only for debug assertions (debug only)
#ifndef NDEBUG
#define ASSERT(e)                                                                                  \
    do                                                                                             \
    {                                                                                              \
        if (!(e))                                                                                  \
        {                                                                                          \
            fprintf(logfilep,                                                                      \
                    "ASSERT FAILED: %s:%d: %s(): ASSERT(%s);\n",                                   \
                    __FILE__,                                                                      \
                    __LINE__,                                                                      \
                    __FUNCTION__,                                                                  \
                    #e);                                                                           \
            fprintf(stdout,                                                                        \
                    "ASSERT FAILED: %s:%d: %s(): ASSERT(%s);\n",                                   \
                    __FILE__,                                                                      \
                    __LINE__,                                                                      \
                    __FUNCTION__,                                                                  \
                    #e);                                                                           \
            fflush(logfilep);                                                                      \
            __builtin_debugtrap();                                                                 \
        }                                                                                          \
    } while (0)
#else
#define ASSERT() (void)
#endif

#define __debugbreak() __builtin_debugtrap()

// cheesy error result checking (always performed)
#define CHECK(chk)                                                                                 \
    do                                                                                             \
    {                                                                                              \
        char result = !!(chk);                                                                     \
        if (!result)                                                                               \
        {                                                                                          \
            fprintf(logfilep,                                                                      \
                    "CHECK FAILED: %s:%d: %s(): CHECK(%s);\n",                                     \
                    __FILE__,                                                                      \
                    __LINE__,                                                                      \
                    __FUNCTION__,                                                                  \
                    #chk);                                                                         \
            fprintf(stdout,                                                                        \
                    "CHECK FAILED: %s:%d: %s(): CHECK(%s);\n",                                     \
                    __FILE__,                                                                      \
                    __LINE__,                                                                      \
                    __FUNCTION__,                                                                  \
                    #chk);                                                                         \
            fflush(logfilep);                                                                      \
            ASSERT(result);                                                                        \
        }                                                                                          \
    } while (0)

#define NUM_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))

// SDL things
extern struct SDL_Surface *  sdl_cursor_image;
extern struct SDL_Cursor *   sdl_cursor;
extern struct SDL_Renderer * sdl_renderer;

// exec
typedef void *   APTR;   /* 32-bit untyped pointer */
typedef int32_t  LONG;   /* signed 32-bit quantity */
typedef uint32_t ULONG;  /* unsigned 32-bit quantity */
typedef int16_t  WORD;   /* signed 16-bit quantity */
typedef uint16_t UWORD;  /* unsigned 16-bit quantity */
typedef int8_t   BYTE;   /* signed 8-bit quantity */
typedef uint8_t  UBYTE;  /* unsigned 8-bit quantity */
typedef char *   STRPTR; /* string pointer (NULL terminated) */
typedef int16_t  SHORT;  /* signed 16-bit quantity (use WORD) */
typedef uint16_t USHORT; /* unsigned 16-bit quantity (use UWORD) */
typedef int16_t  BOOL;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define MEMF_CHIP  (1L << 1)
#define MEMF_CLEAR (1L << 16) /* AllocMem: NULL out area before return */

APTR AllocMem(uint32_t bytesize, uint32_t attributes);
void FreeMem(APTR memoryBlock, uint32_t byteSize);

// input
#define IECODE_UP_PREFIX       0x80
#define IEQUALIFIER_RBUTTON    0x2000
#define IEQUALIFIER_LEFTBUTTON 0x4000

// Gfx
#define JAM1       0 /* jam 1 color into raster */
#define JAM2       1 /* jam 2 colors into raster */
#define COMPLEMENT 2 /* XOR bits into raster */
#define INVERSVID  4 /* inverse video for drawing modes */

#define VP_HIDE 0x2000
#define SPRITES 0x4000
#define HIRES   0x8000

struct BitMap
{
    UWORD         BytesPerRow;
    UWORD         Rows;
    UBYTE         Flags;
    UBYTE         Depth;
    const char *  Name;
    SDL_Surface * Surface;
};

struct RastPort
{
    struct Layer *    Layer;
    struct BitMap *   BitMap;
    BYTE              FgPen;      /* foreground pen for this raster */
    BYTE              BgPen;      /* background pen  */
    BYTE              DrawMode;   /* drawing mode for fill, lines, and text */
    WORD              cp_x, cp_y; /* current pen position */
    struct TextFont * Font;       /* current font address */
};

#define NUM_AMIGA_COLORS 32

struct ColorMap
{
    SDL_Color colors[NUM_AMIGA_COLORS];
};

struct RasInfo /* used by callers to and InitDspC() */
{
    struct RasInfo * Next;
    struct BitMap *  BitMap;
    WORD             RxOffset, RyOffset; /* scroll offsets in this BitMap */
};

struct ViewPort
{
    struct ViewPort * Next;
    struct ColorMap * ColorMap;
    struct RasInfo *  RasInfo;
    WORD              DWidth, DHeight;
    WORD              DxOffset, DyOffset;
    UWORD             Modes;
};

struct View
{
    struct ViewPort * ViewPort;
};

struct GlyphInfo
{
    uint16_t LocationStart;
    uint8_t  BitLength;
    uint8_t  Spacing;
};

struct TextFont
{
    uint8_t            LoChar;
    uint8_t            NumGlyphs;
    SDL_Surface *      Bitmap;
    struct GlyphInfo * Glyphs;
};

UBYTE * AllocRaster(uint32_t width, uint32_t height);
void    InitRastPort(struct RastPort * rp);
LONG    BltBitMap(struct BitMap * srcBitMap,
                  int32_t         xSrc,
                  int32_t         ySrc,
                  struct BitMap * destBitMap,
                  int32_t         xDest,
                  int32_t         yDest,
                  int32_t         xSize,
                  int32_t         ySize,
                  uint32_t        minterm,
                  uint32_t        mask,
                  UBYTE *         tempA);
void    ChangeSprite(struct ViewPort * vp, uint16_t width, uint16_t height, UBYTE * newData);
void    DisownBlitter(void);
void    FreeColorMap(struct ColorMap * colorMap);
struct ColorMap * GetColorMap(int32_t entries);
void              InitBitMap(struct BitMap * bitMap,
                             int32_t         depth,
                             int32_t         width,
                             int32_t         height,
                             const char *    name);
struct TextFont * OpenFont(const char * fntPath, const char * pngPath);
void              FreeFont(struct TextFont * font);
void              InitRastPort(struct RastPort * rp);
void              InitVPort(struct ViewPort * vp);
void              InitView(struct View * view);
void              LoadRGB4(struct ViewPort * vp, UWORD * colors, int32_t count);
void              Move(struct RastPort * rp, int32_t x, int32_t y);
void              OwnBlitter(void);
void RectFill(struct RastPort * rp, int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax);
void ScrollRaster(struct RastPort * rp,
                  int32_t           dx,
                  int32_t           dy,
                  int32_t           xMin,
                  int32_t           yMin,
                  int32_t           xMax,
                  int32_t           yMax);
void SetAPen(struct RastPort * rp, uint32_t pen);
void SetBPen(struct RastPort * rp, uint32_t pen);
void SetDrMd(struct RastPort * rp, uint32_t drawMode);
void SetFont(struct RastPort * rp, struct TextFont * textFont);
void SetRast(struct RastPort * rp, uint32_t pen);
void SetRGB4(struct ViewPort * vp, int32_t index, uint32_t red, uint32_t green, uint32_t blue);
LONG Text(struct RastPort * rp, STRPTR string, uint32_t count);
void WaitBlit(void);

// dos
void Delay(int32_t timeout);
LONG IoErr(void);

#endif
