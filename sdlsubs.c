/* sdl wrappers */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "amigaos.h"        // Xark: most AmigaOS includes (like "amiga39.pre")

#include "ftale.h"

#include <SDL.h>
#include <SDL_image.h>

char raw_asset_fname[128];

BOOL sdl_quit;

uint8_t sdl_key;

struct SDL_Renderer * sdl_renderer;
struct SDL_Window *   sdl_window;
SDL_Joystick *        sdl_controller;
struct SDL_Surface *  sdl_cursor_image;
struct SDL_Cursor *   sdl_cursor;

// TODO: Check if already big-endian
uint32_t swap_endian(uint32_t v)
{
    return ((v >> 24) & 0xff) |             // move byte 3 to byte 0
           ((v << 8) & 0xff0000) |          // move byte 1 to byte 2
           ((v >> 8) & 0xff00) |            // move byte 2 to byte 1
           ((v << 24) & 0xff000000);        // byte 0 to byte 3
}

// TODO: Check if already big-endian
uint16_t swap_endian16(uint16_t v)
{
    return ((v << 8) & 0xff00) |        // move byte 1 to byte 2
           ((v >> 8) & 0x00ff);
}

SDL_Color amiga_color(UWORD color)
{
    SDL_Color sc;
    sc.r = ((color & 0xf00) >> 4) | ((color & 0xf00) >> 8);
    sc.g = ((color & 0xf0) >> 0) | ((color & 0xf0) >> 4);
    sc.b = ((color & 0xf) << 4) | ((color & 0xf) << 0);
    sc.a = 0xff;

    return sc;
}

void print_bitmap_info(char * msg, struct BitMap * bm)
{
    DPRINTF("struct BitMap = %p%s - \"%s\"\n", bm, bm == NULL ? " NULL! " : "", msg);
    if (bm)
    {
        print_surface_info(msg, bm->Surface);
    }
}

void print_surface_info(char * msg, SDL_Surface * s)
{
    DPRINTF("SDL_Surface = %p%s - \"%s\"\n", s, s == NULL ? " NULL! " : "", msg);
    if (s)
    {
        DPRINTF("{\n");
        DPRINTF("  flags = 0x%x\n", s->flags);
        DPRINTF("  format = %p [%s]\n", s->format, SDL_GetPixelFormatName(s->format->format));
        if (s->format->palette)
        {
            DPRINTF("  format.palette = %p [%d colors]\n",
                    s->format->palette,
                    s->format->palette->ncolors);
        }
        DPRINTF("  w=%d, h=%d\n", s->w, s->h);
        DPRINTF("  pitch=%d\n", s->pitch);
        DPRINTF("  pixels=%p\n", s->pixels);
        DPRINTF("  userdata=%p\n", s->userdata);
        DPRINTF("  clip={%d, %d, %d, %d}\n",
                s->clip_rect.x,
                s->clip_rect.y,
                s->clip_rect.w,
                s->clip_rect.h);
        DPRINTF("}\n");
    }
}

const char * c_string(const char * s, int maxlen)
{
    static char str[256];
    char *      p = str;
    if (maxlen >= (int)sizeof(str))
    {
        maxlen = (int)sizeof(str) - 3;
    }

    *p++ = '\"';
    int l;
    for (l = 0; l < maxlen; l++)
    {
        char c = *s;
        if (c == 0)
        {
            break;
        }
        else if (c == '\"')
        {
            p += sprintf(p, "\\\"");
        }
        else if (c == '\r')
        {
            p += sprintf(p, "\\r");
        }
        else if (c == '\b')
        {
            p += sprintf(p, "\\b");
        }
        // else if (c < ' ' || c > '~')
        // {
        //     p += sprintf(p, "\\x%02x", c & 0xff);
        // }
        else
        {
            *p++ = c;
        }
        s++;
    }
    *p++ = '\"';
    if (*s)
    {
        p += sprintf(p, " ...");
    }
    *p = '\0';

    return str;
}

void save_raw_asset(const char * fname, void * ptr, int32_t len, int appendflag)
{
    (void)fname;
    (void)ptr;
    (void)len;
    (void)appendflag;
#if SAVE_RAW
    FILE * rp;

    RUNLOGF("<= *** save_raw_asset(\"%s\", %p, %d)", fname, ptr, len);

    if ((rp = fopen(fname, appendflag ? "w+" : "w")) != NULL)
    {
        CHECK(1 == fwrite(ptr, len, 1, rp));

        fclose(rp);
    }
#endif
}

int sdl_init(void)
{
    char        time_stamp[64];
    time_t      now        = time(NULL);
    struct tm * local_time = localtime(&now);
    strftime(time_stamp, sizeof(time_stamp), "%Y%m%d-%H:%M:%S", local_time);

    if ((logfilep = fopen("FTA-gamerun.log", "w")) == NULL)
    {
        printf("ERROR: Can't open log \"%s\": %s\n", "FTA-gamerun.log", strerror(errno));
        return EXIT_FAILURE;
    }

    RUNLOGF("*** FTA/SDL2 FTA-gamerun.log - %s", time_stamp);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    sdl_window = SDL_CreateWindow("Faery Tale Adventure",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  640,
                                  480,
                                  SDL_WINDOW_SHOWN);

    sdl_renderer =
        SDL_CreateRenderer(sdl_window, -1, /* SDL_RENDERER_SOFTWARE | */ SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetScale(sdl_renderer, 1, 1);
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x40, 0x90, 255);        // Amiga blue
    SDL_RenderClear(sdl_renderer);
    SDL_RenderPresent(sdl_renderer);
    // SDL_StartTextInput();

    if (SDL_NumJoysticks() < 1)
    {
        RUNLOGF("WARN: No SDL joysticks detected.\n");
    }
    else
    {
        // Load joystick
        sdl_controller = SDL_JoystickOpen(0);
        if (sdl_controller == NULL)
        {
            RUNLOGF("WARN: Joystick error : %s\n", SDL_GetError());
        }
        else
        {
            RUNLOGF("NOTE: Using joystick 0 : %s\n", SDL_JoystickName(sdl_controller));
        }
    }

    return 0;
}

void sdl_exit(int retval)
{
    RUNLOGF("QUIT: exiting, code %d...", retval);

    SDL_JoystickClose(sdl_controller);
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_Quit();

    exit(retval);
}

uint16_t hack_cursor[] = {0x0000, 0x0c74, 0x0d96, 0x0fca};  // TODO: get from VP

void sdl_update_cursor(struct ViewPort * vp)
{
    (void) vp;
    SDL_Color t                                  = {0, 0, 0, 0};
    sdl_cursor_image->format->palette->colors[0] = t;
    for (int i = 1; i < 4; i++)
    {
        uint16_t  ac = hack_cursor[i];
        SDL_Color sc = amiga_color(ac);        // 16 is offset due to sprite 0
        sdl_cursor_image->format->palette->colors[i] = sc;

        RUNLOGF("... [sprite #%2d %02x%02x%02x%02x = %04x", i, sc.r, sc.g, sc.b, sc.a, ac);
    }

    sdl_cursor = SDL_CreateColorCursor(sdl_cursor_image, 0, 0);
    SDL_SetCursor(sdl_cursor);
    SDL_ShowCursor(SDL_ENABLE);
}

#define FLIPSPAM 0

void sdl_endframe(void)
{
    sdl_pump();

    // draw Amiga View
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(sdl_renderer);

    struct ViewPort * curvp = v.ViewPort;

    sdl_update_cursor(&vp_page);

    int vnum = 0;
    (void)vnum;
    while (curvp)
    {
#if FLIPSPAM
        DPRINTF("ViewPort #%d\n", vnum);
        DPRINTF("  ColorMap = %p\n", curvp->ColorMap);
        DPRINTF("  RasInfo = %p\n", curvp->RasInfo);
        DPRINTF("  DWidth, DHeight = %d, %d\n", curvp->DWidth, curvp->DHeight);
        DPRINTF("  DxOffset, DyOffset = %d, %d\n", curvp->DxOffset, curvp->DyOffset);
        DPRINTF("  Modes = 0x%x\n", curvp->Modes);
#endif

        SDL_Surface * s = curvp->RasInfo->BitMap->Surface;
        // uint16_t *    ac = curvp->ColorMap->colors;
        // SDL_Color *   sc = s->format->palette->colors;
        // for (int i = 0; i < NUM_AMIGA_COLORS; i++)
        // {
        //     sc[i].r = ((ac[i] & 0xf00) >> 4) | ((ac[i] & 0xf00) >> 8);
        //     sc[i].g = ((ac[i] & 0xf0) >> 0) | ((ac[i] & 0xf0) >> 4);
        //     sc[i].b = ((ac[i] & 0xf) << 4) | ((ac[i] & 0xf) << 0);
        // }
#if FLIPSPAM
        print_bitmap_info("RasInfo.BitMap", curvp->RasInfo->BitMap);
#endif

        // ignore if height <= 0
        if (curvp->DHeight > 0)
        {
#if FLIPSPAM
            DPRINTF("... [render surface to %d,%d]", curvp->DxOffset, curvp->DyOffset);
#endif

            SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, s);
            SDL_Rect      dr      = {curvp->DxOffset, curvp->DyOffset, 0x7fff, 0x7fff};
            SDL_RenderCopy(sdl_renderer, texture, NULL, &dr);
        }
        else
        {
            DPRINT("... [height <= 0]");
        }

        curvp = curvp->Next;
        vnum++;
    }

#if 0
    //    SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, rp->BitMap->Surface);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, rp_text.BitMap->Surface);

    SDL_RenderClear(sdl_renderer);
    SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
#endif
    SDL_RenderPresent(sdl_renderer);
    DPRINT("=== SDL_RenderPresent(sdl_renderer)\n\n");
}

void sdl_pump(void)
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                /* Quit */
                RUNLOG("... SDL_QUIT event");

                sdl_quit = TRUE;
                break;

            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    // TODO: ESC to quit is abrupt, but nice for development
                    RUNLOG("... ESC pressed");
                    sdl_quit = TRUE;
                }
                else
                {
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2 ||
                        e.key.keysym.sym == SDLK_KP_ENTER)
                    {
                        sdl_key = '\r';
                    }
                    else if (e.key.keysym.sym == SDLK_BACKSPACE || e.key.keysym.sym == SDLK_DELETE)
                    {
                        sdl_key = '\b';
                    }
                    else
                    {
                        sdl_key = e.key.keysym.sym;
                    }
                    // {
                    //     char kstr[2] = {0};
                    //     kstr[0]      = (char)e.key.keysym.sym;
                    //     RUNLOGF("... KEYDOWN 0x%02x %s", sdl_key, c_string(kstr, 1));
                    // }
                }
                break;
            case SDL_KEYUP:
                if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2 ||
                    e.key.keysym.sym == SDLK_KP_ENTER)
                {
                    sdl_key = '\r' | IECODE_UP_PREFIX;
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE || e.key.keysym.sym == SDLK_DELETE)
                {
                    sdl_key = '\b' | IECODE_UP_PREFIX;
                }
                else
                {
                    sdl_key = e.key.keysym.sym | IECODE_UP_PREFIX;
                }
                // {
                //     char kstr[2] = {0};
                //     kstr[0]      = (char)e.key.keysym.sym;
                //     RUNLOGF("... KEYUP 0x%02x %s", sdl_key, c_string(kstr, 1));
                // }
                break;
            case SDL_MOUSEMOTION:
                handler_data.xsprite = e.motion.x;
                handler_data.ysprite = e.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                handler_data.xsprite = e.motion.x;
                handler_data.ysprite = e.motion.y;
                RUNLOGF("*SDL* mousedown: %d,%d", handler_data.xsprite, handler_data.ysprite);

                break;
            case SDL_MOUSEBUTTONUP:
                RUNLOGF("*SDL* mouseup: %d,%d", handler_data.xsprite, handler_data.ysprite);
                break;
        }
    }

    if (sdl_quit)
    {
        sdl_exit(0);
    }
}

BOOL unpack_png(char * filename, struct BitMap * bitmap, int16_t wx, int16_t y)
{
    RUNLOGF("<= unpack_png(\"%s\", %p, %d, %d)", filename, bitmap, wx, y);

    SDL_Surface * img = IMG_Load(filename);
    if (!img)
    {
        RUNLOGF("... failed: %s", SDL_GetError());
        return FALSE;
    }
    RUNLOGF("... [size %d x %d]", img->w, img->h);

    SDL_Rect dest = {wx * 16, y, 0x7fff, 0x7fff};
    SDL_BlitSurface(img, NULL, bitmap->Surface, &dest);

    return TRUE;
}