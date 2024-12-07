/* sdl wrappers */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ftale.h"

#include <SDL.h>
#include <SDL_image.h>

#define DEBUG_WINDOW 0

char raw_asset_fname[128];
char asset_fname[128];

BOOL    big_endian;
BOOL    sdl_quit;
BOOL    sdl_screenshot;
int16_t sdl_qualifier;

struct SDL_Renderer * sdl_renderer;
struct SDL_Window *   sdl_window;
#if DEBUG_WINDOW
struct SDL_Renderer * sdl_debug_renderer;
struct SDL_Window *   sdl_debug_window;
#endif
int32_t              sdl_controllerIndex = -1;
SDL_GameController * sdl_controller;
struct SDL_Surface * sdl_cursor_image;
struct SDL_Cursor *  sdl_cursor;

float sdl_window_scale = 2.0f;
#define Y_ASPECT() (1.0)        // (480.0 / 400)
uint32_t frame_counter;

uint32_t swap_endian(uint32_t v)
{
    if (big_endian)
    {
        return v;
    }
    return ((v >> 24) & 0xff) |             // move byte 3 to byte 0
           ((v << 8) & 0xff0000) |          // move byte 1 to byte 2
           ((v >> 8) & 0xff00) |            // move byte 2 to byte 1
           ((v << 24) & 0xff000000);        // byte 0 to byte 3
}

uint16_t swap_endian16(uint16_t v)
{
    if (big_endian)
    {
        return v;
    }
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
        uint8_t c = *s;
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
        else if (c < ' ' || c > '~')
        {
            p += sprintf(p, "\\x%02x", c);
        }
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


int sdl_init(void)
{
    union
    {
        uint8_t  byte[2];
        uint16_t word;
    } endian;
    char        time_stamp[64];
    time_t      now        = time(NULL);
    struct tm * local_time = localtime(&now);
    strftime(time_stamp, sizeof(time_stamp), "%Y%m%d-%H:%M:%S", local_time);

    if ((logfilep = fopen("logs/FTA-gamerun.log", "w")) == NULL)
    {
        printf("ERROR: Can't open log \"%s\": %s\n", "logs/FTA-gamerun.log", strerror(errno));
        return EXIT_FAILURE;
    }

    RUNLOGF("*** FTA/SDL2 logs/FTA-gamerun.log - %s", time_stamp);

    endian.word = 0x0001;
    big_endian  = endian.byte[1];

    RUNLOGF("CPU is %s endian", big_endian ? "BIG" : "LITTLE");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) !=
        0)
    {
        fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

#if DEBUG_WINDOW
    sdl_debug_window = SDL_CreateWindow(
        "FTA Debug", SDL_WINDOWPOS_CENTERED_DISPLAY(1), 10, 320, 200, SDL_WINDOW_SHOWN);
    sdl_debug_renderer = SDL_CreateRenderer(sdl_debug_window, -1, 0);
    SDL_RenderSetScale(sdl_renderer, 640.0 / 640, Y_ASPECT());
    SDL_SetRenderDrawColor(sdl_debug_renderer, 0x20, 0x00, 0x00, 255);
    SDL_RenderClear(sdl_debug_renderer);
    SDL_RenderPresent(sdl_debug_renderer);
#endif

    sdl_window = SDL_CreateWindow("Faery Tale Adventure",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  640 * sdl_window_scale,
                                  400 * sdl_window_scale,
                                  SDL_WINDOW_SHOWN);
    sdl_renderer =
        SDL_CreateRenderer(sdl_window, -1, /* SDL_RENDERER_SOFTWARE | */ SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetScale(
        sdl_renderer, (640.0 / 640) * sdl_window_scale, Y_ASPECT() * sdl_window_scale);

    // This small loop lets SDL2 process some initial events (like controllers)
    for (int f = 0; f < 30; f++)
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 255);
        SDL_RenderClear(sdl_renderer);
        SDL_RenderPresent(sdl_renderer);
        sdl_pump();
    }

    return 0;
}

void sdl_exit(int retval)
{
    RUNLOGF("\ndl_exit: exiting, exit code %d", retval);

    SDL_GameControllerClose(sdl_controller);
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_Quit();

    exit(retval);
}

// TODO: I think a software rendered cursor may be desirable
void sdl_update_cursor(struct ViewPort * vp)
{
    // use colors from VP
    SDL_Color sp_pal[4] = {{0, 0, 0, 0}};        // 0 transparent
    for (int i = 1; i < 4; i++)
    {
        sp_pal[i] = vp->ColorMap->colors[i];
    }
    SDL_SetPaletteColors(sdl_cursor_image->format->palette, sp_pal, 0, 4);
    sdl_cursor = SDL_CreateColorCursor(sdl_cursor_image, 0, 0);
    SDL_SetCursor(sdl_cursor);
    SDL_ShowCursor(SDL_ENABLE);
}

#define FLIPSPAM 0


void sdl_endframe(void)
{
    sdl_pump();

    sdl_update_cursor(v.ViewPort);
    sdl_drawframe();

    SDL_RenderPresent(sdl_renderer);

    DPRINTF("=== SDL_RenderPresent(sdl_renderer) [frame %8d] ===\n\n", frame_counter);

    if (sdl_quit)
    {
        RUNLOG("*SDL* SDL_QUIT requested");
        sdl_exit(0);
    }

    frame_counter++;
}

void sdl_drawframe(void)
{
    // draw Amiga View
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(sdl_renderer);

    struct ViewPort * curvp = v.ViewPort;
    sdl_update_cursor(curvp);

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
        // use colors fromin VP
        SDL_Color * ac = curvp->ColorMap->colors;
        SDL_Color * sc = s->format->palette->colors;
        for (int i = 0; i < NUM_AMIGA_COLORS; i++)
        {
            sc[i] = ac[i];
            sc[i] = ac[i];
            sc[i] = ac[i];
            sc[i] = ac[i];
        }

        SDL_SetPaletteColors(s->format->palette, sc, 0, NUM_AMIGA_COLORS);

#if FLIPSPAM
        print_bitmap_info("RasInfo.BitMap", curvp->RasInfo->BitMap);
#endif

        float x_window_scale = 2.0f;
        float y_window_scale = 2.0f;

        if (curvp->Modes & HIRES)
        {
            x_window_scale = 1.0f;
        }

        // ignore if height <= 0
        if (curvp->DHeight > 0)
        {
            DPRINTF("... [render VP #%d \"%s\" to %d,%d - %dx%d, xy_scale %.02f, %.02f]%s\n",
                    vnum,
                    curvp->RasInfo->BitMap->Name,
                    curvp->DxOffset,
                    curvp->DyOffset,
                    curvp->DWidth,
                    curvp->DHeight,
                    x_window_scale,
                    y_window_scale,
                    curvp->Modes & HIRES ? " HIRES" : "");
#if 0        // show colormap
            for (int c = 1; c < 32; c++)
            {
                SDL_Rect cr = {c * 4, 1, 3, 3};
                SDL_FillRect(s, &cr, c);
            }
#endif
            SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, s);
            //            SDL_Rect      sr      = {0, 0, curvp->DWidth, curvp->DHeight};
            SDL_Rect dr = {curvp->DxOffset * x_window_scale,
                           curvp->DyOffset * y_window_scale,
                           curvp->DWidth * x_window_scale,
                           curvp->DHeight * y_window_scale};
            SDL_RenderCopy(sdl_renderer, texture, NULL, &dr);
        }
        else
        {
            DPRINT("... [height <= 0]\n");
        }

        curvp = curvp->Next;
        vnum++;
    }

    if (sdl_screenshot)
    {
        sdl_save_screenshot("logs/fta-screenshot-f%06d.png");
        sdl_screenshot = FALSE;
    }
    else if (sdl_quit)
    {
        sdl_save_screenshot("logs/fta-screenshot-quit.png");
    }
}

void sdl_save_screenshot(char * name)
{
    int           w = 0, h = 0;
    char          save_name[256] = {0};
    SDL_Surface * screen_shot    = NULL;

    snprintf(save_name, sizeof(save_name) - 1, name, frame_counter);
    SDL_GetRendererOutputSize(sdl_renderer, &w, &h);
    screen_shot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(
        sdl_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screen_shot->pixels, screen_shot->pitch);
    RUNLOGF("*SDL* Saving screeen shot \"%s\"", save_name);
    IMG_SavePNG(screen_shot, save_name);
    SDL_FreeSurface(screen_shot);
}

void add_to_keybuf(int key)
{
    handler_data.keybuf[handler_data.laydown] = key;
    UBYTE ld                                  = (handler_data.laydown + 1) & (KEYBUFFER_SIZE - 1);
    if (ld != handler_data.pickup)
    {
        handler_data.laydown = ld;
    }
    else
    {
        RUNLOGF("*SDL* add_to_keybuf buffer full (%d keys)", KEYBUFFER_SIZE);
    }
}

int16_t get_from_keybuf()
{
    int16_t key = 0;
    if (handler_data.pickup != handler_data.laydown)
    {
        key                 = handler_data.keybuf[handler_data.pickup];
        handler_data.pickup = (handler_data.pickup + 1) & (KEYBUFFER_SIZE - 1);
    }

    return key;
}

void ft_mouse_button(int16_t qual)
{
    int16_t qual_change = qual ^ handler_data.qualifier;
    // did left menu button change?
    if (qual_change & IEQUALIFIER_LEFTBUTTON)
    {
        if (qual & IEQUALIFIER_LEFTBUTTON)        // was left menu button pressed?
        {
            if (handler_data.xsprite >= FTMOUSE_MENU_MIN_X &&
                handler_data.xsprite <= FTMOUSE_MENU_MAX_X)
            {
                if (handler_data.ysprite >= FTMOUSE_MENU_MIN_Y)
                {
                    int16_t menu_key =
                        (((handler_data.ysprite - FTMOUSE_MENU_MIN_Y) / FTMOUSE_MENU_HEIGHT) * 2) +
                        'a';
                    if (handler_data.xsprite >= FTMOUSE_MENU_MID_X)
                    {
                        menu_key += 1;
                    }
                    handler_data.lastmenu = menu_key;

                    RUNLOGF("*SDL* add_to_keybuf menu option:%d ['%c'] @ %d, %d",
                            menu_key,
                            menu_key,
                            handler_data.xsprite,
                            handler_data.ysprite);
                    add_to_keybuf(menu_key);        // queue menu down action
                }
            }
        }
        else if (handler_data.lastmenu != 0)        // menu with left menu button released?
        {
            int16_t last_menu_key = handler_data.lastmenu |= IECODE_UP_PREFIX;
            handler_data.lastmenu = 0;

            add_to_keybuf(last_menu_key);        // queue menu up action
        }
    }
    handler_data.qualifier = qual;
}

void ft_mouse_pos(int16_t x, int16_t y)
{
    // Amiga mouse is ~320x200 resolution
    x = ((x / sdl_window_scale) / 2);
    y = ((y / sdl_window_scale) / 2);
    if (x < FTMOUSE_MIN_X)
    {
        x = FTMOUSE_MIN_X;
    }
    if (x > FTMOUSE_MAX_X)
    {
        x = FTMOUSE_MAX_X;
    }
    if (y < FTMOUSE_MIN_Y)
    {
        y = FTMOUSE_MIN_Y;
    }
    if (y > FTMOUSE_MAX_Y)
    {
        y = FTMOUSE_MAX_Y;
    }
    handler_data.xsprite = x;
    handler_data.ysprite = y;
}

// Original AmigaCode -> FT_KEY table
// See https://wiki.amigaos.net/wiki/Keymap_Library#Keyboard_Layout
// keytrans        dc.b        "`1234567890-=\?0"
//                         dc.b        "QWERTYUIOP{}?",26,25,24
//                         dc.b        "ASDFGHJKL:???",27,29,23
//                         dc.b        "?ZXCVBNM,.??.",20,21,22
//                         dc.b        $20,$08,$09,$0D,$0D,$1B,$7F,0,0,0,$2D,0,1,2,3,4
//                         dc.b        10,11,12,13,14,15,16,17,18,19,0,0,0,0,0,0
//
struct
{
    int32_t sdl_keycode;
    int32_t ft_keycode;
} sdl_to_ft_key[] = {
    // SDL_KEY, FT_KEY             // Amiga KeyCode
    /* {SDLK_BACKQUOTE, '`'},*/        // 00 (screenshot)
    {SDLK_1, '1'},                     // 01
    {SDLK_2, '2'},                     // 02
    {SDLK_3, '3'},                     // 03
    {SDLK_4, '4'},                     // 04
    {SDLK_5, '5'},                     // 05
    {SDLK_6, '6'},                     // 06
    {SDLK_7, '7'},                     // 07
    {SDLK_8, '8'},                     // 08
    {SDLK_9, '9'},                     // 09
    {SDLK_0, '0'},                     // 0A
    {SDLK_MINUS, '-'},                 // 0B
    {SDLK_EQUALS, '='},                // 0C
    {SDLK_BACKSLASH, '\\'},            // 0D
                                       // 0E
    {SDLK_KP_0, '0'},                  // 0F
    {SDLK_q, 'Q'},                     // 10
    {SDLK_w, 'W'},                     // 11
    {SDLK_e, 'E'},                     // 12
    {SDLK_r, 'R'},                     // 13
    {SDLK_t, 'T'},                     // 14
    {SDLK_y, 'Y'},                     // 15
    {SDLK_i, 'I'},                     // 16
    {SDLK_o, 'O'},                     // 17
    {SDLK_u, 'U'},                     // 18
    {SDLK_p, 'P'},                     // 19
    {SDLK_LEFTBRACKET, '{'},           // 1A
    {SDLK_RIGHTBRACKET, '}'},          // 1B
                                       // 1C
    {SDLK_KP_1, 26},                   // 1D
    {SDLK_KP_2, 25},                   // 1E
    {SDLK_KP_3, 24},                   // 1F
    {SDLK_a, 'A'},                     // 20
    {SDLK_s, 'S'},                     // 21
    {SDLK_d, 'D'},                     // 22
    {SDLK_f, 'F'},                     // 23
    {SDLK_g, 'G'},                     // 24
    {SDLK_h, 'H'},                     // 25
    {SDLK_j, 'J'},                     // 26
    {SDLK_k, 'K'},                     // 27
    {SDLK_l, 'L'},                     // 28
    {SDLK_SEMICOLON, ':'},             // 29
                                       // 2A
                                       // 2B
                                       // 2C
    {SDLK_KP_4, 27},                   // 2D
    {SDLK_KP_5, 29},                   // 2E
    {SDLK_KP_6, 23},                   // 2F
                                       // 30
    {SDLK_z, 'Z'},                     // 31
    {SDLK_x, 'X'},                     // 32
    {SDLK_c, 'C'},                     // 33
    {SDLK_v, 'V'},                     // 34
    {SDLK_b, 'B'},                     // 35
    {SDLK_n, 'N'},                     // 36
    {SDLK_m, 'M'},                     // 37
    {SDLK_COMMA, ','},                 // 38
    {SDLK_PERIOD, '.'},                // 39
                                       // 3A
                                       // 3B
    {SDLK_KP_PERIOD, '.'},             // 3C
    {SDLK_KP_7, 20},                   // 3D
    {SDLK_KP_8, 21},                   // 3E
    {SDLK_KP_9, 22},                   // 3F
    {SDLK_SPACE, ' '},                 // 40
    {SDLK_BACKSPACE, '\b'},            // 41
    {SDLK_TAB, '\t'},                  // 42
    {SDLK_RETURN, '\r'},               // 43
    {SDLK_KP_ENTER, '\r'},             // 44
    {SDLK_ESCAPE, '\x1b'},             // 45
    {SDLK_DELETE, '\x7f'},             // 46
                                       // 47
                                       // 48
                                       // 49
    {SDLK_KP_MINUS, '-'},              // 4A
                                       // 4B
    {SDLK_UP, 1},                      // 4C
    {SDLK_DOWN, 2},                    // 4D
    {SDLK_RIGHT, 3},                   // 4E
    {SDLK_LEFT, 4},                    // 4F
    {SDLK_F1, 10},                     // 50
    {SDLK_F2, 11},                     // 51
    {SDLK_F3, 12},                     // 52
    {SDLK_F4, 13},                     // 53
    {SDLK_F5, 14},                     // 54
    {SDLK_F6, 15},                     // 55
    {SDLK_F7, 16},                     // 56
    {SDLK_F8, 17},                     // 57
    {SDLK_F9, 18},                     // 58
    {SDLK_F10, 19},                    // 59
};

void sdl_pump(void)
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_WINDOWEVENT:
                switch (e.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        sdl_quit = TRUE;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_QUIT:
                sdl_quit = TRUE;
                break;

            case SDL_KEYDOWN:
                // Ctrl-C or Ctrl-ESC to quit
                if (e.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL) &&
                    ((e.key.keysym.sym == SDLK_c) || (e.key.keysym.sym == SDLK_ESCAPE)))
                {
                    sdl_quit = TRUE;
                }
                else if (e.key.repeat == 0)        // ignore autorepeat
                {
                    cheat1 = (e.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) ? TRUE : FALSE;
                    cheat2 = (e.key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ? TRUE : FALSE;

                    if (e.key.keysym.sym == SDLK_BACKQUOTE)
                    {
                        sdl_screenshot = TRUE;
                    }

                    for (uint32_t ki = 0; ki < NUM_ELEMENTS(sdl_to_ft_key); ki++)
                    {
                        if (e.key.keysym.sym == sdl_to_ft_key[ki].sdl_keycode)
                        {
                            add_to_keybuf(sdl_to_ft_key[ki].ft_keycode);
                            break;
                        }
                    }
                }
                break;

            case SDL_KEYUP:
                cheat1 = (e.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) ? TRUE : FALSE;
                cheat2 = (e.key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ? TRUE : FALSE;

                for (uint32_t ki = 0; ki < NUM_ELEMENTS(sdl_to_ft_key); ki++)
                {
                    if (e.key.keysym.sym == sdl_to_ft_key[ki].sdl_keycode)
                    {
                        add_to_keybuf(sdl_to_ft_key[ki].ft_keycode | IECODE_UP_PREFIX);
                        break;
                    }
                }
                break;

            case SDL_MOUSEMOTION:
                ft_mouse_pos(e.motion.x, e.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                ft_mouse_pos(e.motion.x, e.motion.y);
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        RUNLOGF("*SDL* SDL_MOUSEBUTTONDOWN: %d,%d LEFT",
                                handler_data.xsprite,
                                handler_data.ysprite);

                        sdl_qualifier |= IEQUALIFIER_LEFTBUTTON;
                        break;

                    case SDL_BUTTON_RIGHT:
                        RUNLOGF("*SDL* SDL_MOUSEBUTTONDOWN: %d,%d RIGHT",
                                handler_data.xsprite,
                                handler_data.ysprite);
                        sdl_qualifier |= IEQUALIFIER_RBUTTON;
                        break;

                    case SDL_BUTTON_MIDDLE:
                        RUNLOGF("*SDL* SDL_MOUSEBUTTONDOWN: %d,%d MIDDLE",
                                handler_data.xsprite,
                                handler_data.ysprite);
                        sdl_qualifier |= IEQUALIFIER_MIDBUTTON;
                        break;
                }
                ft_mouse_button(sdl_qualifier);
                break;

            case SDL_MOUSEBUTTONUP:
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        RUNLOGF("*SDL* SDL_MOUSEBUTTONUP: %d,%d LEFT",
                                handler_data.xsprite,
                                handler_data.ysprite);
                        sdl_qualifier &= ~IEQUALIFIER_LEFTBUTTON;
                        break;

                    case SDL_BUTTON_RIGHT:
                        RUNLOGF("*SDL* SDL_MOUSEBUTTONUP: %d,%d RIGHT",
                                handler_data.xsprite,
                                handler_data.ysprite);
                        sdl_qualifier &= ~IEQUALIFIER_RBUTTON;
                        break;

                    case SDL_BUTTON_MIDDLE:
                        RUNLOGF("*SDL* SDL_MOUSEBUTTONUP: %d,%d MIDDLE",
                                handler_data.xsprite,
                                handler_data.ysprite);
                        sdl_qualifier &= ~IEQUALIFIER_MIDBUTTON;
                        break;
                }
                ft_mouse_button(sdl_qualifier);
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                RUNLOGF("*SDL* SDL_CONTROLLERBUTTONDOWN: #%d button[%d] DOWN",
                        e.cdevice.which,
                        e.cbutton.button);
                break;

            case SDL_CONTROLLERBUTTONUP:
                RUNLOGF("*SDL* SDL_CONTROLLERBUTTONUP: #%d button[%d] UP",
                        e.cdevice.which,
                        e.cbutton.button);
                break;

            case SDL_CONTROLLERAXISMOTION:
                RUNLOGF("*SDL* SDL_CONTROLLERAXISMOTION: #%d, axis[%d]=%d",
                        e.cdevice.which,
                        e.caxis.axis,
                        e.caxis.value);
                break;

            case SDL_CONTROLLERDEVICEADDED:
                RUNLOGF("*SDL* SDL_CONTROLLERDEVICEADDED: #%d", e.cdevice.which);
                if (sdl_controller == NULL)
                {
                    sdl_controller = SDL_GameControllerOpen(e.cdevice.which);

                    if (sdl_controller)
                    {
                        sdl_controllerIndex = e.cdevice.which;
                        RUNLOGF("*SDL* Controller %d ADDED : %s\n",
                                e.cdevice.which,
                                SDL_GameControllerName(sdl_controller));
                    }
                    else
                    {
                        RUNLOGF(
                            "*SDL* Controller #%d ERROR : %s\n", e.cdevice.which, SDL_GetError());
                    }
                }
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                RUNLOGF("*SDL* SDL_CONTROLLERDEVICEREMOVED: #%d", e.cdevice.which);

                if (sdl_controllerIndex == e.cdevice.which)
                {
                    SDL_GameControllerClose(sdl_controller);
                    sdl_controller      = NULL;
                    sdl_controllerIndex = -1;

                    RUNLOGF("*SDL* Controller #%d REMOVED\n", e.cdevice.which);
                }
                break;
        }
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
    RUNLOGF("... [size %d x %d %s]", img->w, img->h, SDL_GetPixelFormatName(img->format->format));

    SDL_Rect dest = {wx * 8, y, 0x7fff, 0x7fff};
    sdl_blitsurface8(img, NULL, bitmap->Surface, &dest);

#if DEBUG_WINDOW        // test code to see image
    SDL_Texture * ttex = SDL_CreateTextureFromSurface(sdl_debug_renderer, img);
    int32_t       w    = img->w;
    int32_t       h    = img->h;
    if (img->w > 320)
    {
        h <<= 1;
    }
    else
    {
        w <<= 1;
        h <<= 1;
    }
    SDL_SetWindowSize(sdl_debug_window, w, h * (480.0 / 400));
    SDL_RenderSetScale(sdl_debug_renderer, (float)w / img->w, (480.0 / 400));
    SDL_RenderClear(sdl_debug_renderer);
    SDL_RenderCopy(sdl_debug_renderer, ttex, NULL, NULL);
    SDL_SetRenderDrawColor(sdl_debug_renderer, 0x20, 0x00, 0x00, 255);
    SDL_RenderPresent(sdl_debug_renderer);
#endif

    SDL_FreeSurface(img);

    return TRUE;
}

void sdl_blitsurface8(SDL_Surface * src, SDL_Rect * sr, SDL_Surface * dest, SDL_Rect * dr)
{
    ASSERT(src->format->format == SDL_PIXELFORMAT_INDEX8 &&
           dest->format->format == SDL_PIXELFORMAT_INDEX8);
    SDL_Rect ssr = {0, 0, src->w, src->h};
    if (!sr)
    {
        sr = &ssr;
    }
    SDL_Rect sdr = {0, 0, dest->w, dest->h};
    if (!dr)
    {
        dr = &sdr;
    }
    if (!SDL_LockSurface(src))
    {
        if (!SDL_LockSurface(dest))
        {
            UBYTE * sp = src->pixels + (sr->y * src->pitch) + sr->x;
            UBYTE * dp = dest->pixels + (dr->y * dest->pitch) + dr->x;
            for (int16_t v = 0; v < sr->h; v++)
            {
                memcpy(dp, sp, sr->w);
                sp += src->pitch;
                dp += dest->pitch;
            }
            SDL_UnlockSurface(dest);
        }
        SDL_UnlockSurface(src);
    }
}

void sdl_blitsurface8_transmask(SDL_Surface * src,
                                SDL_Rect *    sr,
                                SDL_Surface * dest,
                                SDL_Rect *    dr,
                                UBYTE         maskbyte)
{
    ASSERT(src->format->format == SDL_PIXELFORMAT_INDEX8 &&
           dest->format->format == SDL_PIXELFORMAT_INDEX8);

    if (!SDL_LockSurface(src))
    {
        if (!SDL_LockSurface(dest))
        {
            UBYTE * sp = src->pixels + (sr->y * src->pitch) + sr->x;
            UBYTE * dp = dest->pixels + (dr->y * dest->pitch) + dr->x;
            for (int16_t v = 0; v < sr->h; v++)
            {
                int16_t w   = sr->w;
                UBYTE * scp = sp;
                UBYTE * dcp = dp;
                while (w--)
                {
                    if (*scp)
                    {
                        *dcp = *scp & maskbyte;
                    }
                    scp++;
                    dcp++;
                }
                sp += src->pitch;
                dp += dest->pitch;
            }
            SDL_UnlockSurface(dest);
        }
        SDL_UnlockSurface(src);
    }
}

void sdl_blitsurface8_or_bitplane(SDL_Surface * src,
                                  SDL_Rect *    sr,
                                  SDL_Surface * dest,
                                  SDL_Rect *    dr,
                                  UBYTE         planebyte)
{
    ASSERT(src->format->format == SDL_PIXELFORMAT_INDEX8 &&
           dest->format->format == SDL_PIXELFORMAT_INDEX8);

    if (!SDL_LockSurface(src))
    {
        if (!SDL_LockSurface(dest))
        {
            UBYTE * sp = src->pixels + (sr->y * src->pitch) + sr->x;
            UBYTE * dp = dest->pixels + (dr->y * dest->pitch) + dr->x;
            for (int16_t v = 0; v < sr->h; v++)
            {
                int16_t w   = sr->w;
                UBYTE * scp = sp;
                UBYTE * dcp = dp;
                while (w--)
                {
                    *dcp = (*dcp & ~planebyte) | (*scp & planebyte);
                    scp++;
                    dcp++;
                }
                sp += src->pitch;
                dp += dest->pitch;
            }
            SDL_UnlockSurface(dest);
        }
        SDL_UnlockSurface(src);
    }
}

void sdl_extract_bitplane(SDL_Surface * dest, UBYTE * planedata, UBYTE planemask)
{
    if (!SDL_LockSurface(dest))
    {
        UBYTE * dp = dest->pixels;
        for (int16_t v = 0; v < dest->h; v++)
        {
            UWORD bit = 0x80;
            for (int16_t h = 0; h < dest->w; h++)
            {
                if (*planedata & bit)
                {
                    dp[h] |= planemask;
                }

                bit >>= 1;
                if (!bit)
                {
                    bit = 0x80;
                    planedata++;
                }
            }
            dp += dest->pitch;
        }
        SDL_UnlockSurface(dest);
    }
}

void save_raw_asset(const char * fname, void * ptr, int32_t len, int appendflag)
{
    (void)fname;
    (void)ptr;
    (void)len;
    FILE * rp;

    RUNLOGF("<= *** save_raw_asset(\"%s\", %p, %d)", fname, ptr, len);

    if ((rp = fopen(fname, appendflag ? "a" : "w")) != NULL)
    {
        CHECK(1 == fwrite(ptr, len, 1, rp));

        fclose(rp);
    }
}

void save_png_1bpp_asset(char * fname, void * ptr, int width, int height)
{
    SDL_Surface * s = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    s->format->palette->colors[0].r = 0x0;
    s->format->palette->colors[0].g = 0x0;
    s->format->palette->colors[0].b = 0x0;
    s->format->palette->colors[0].a = 0xff;

    s->format->palette->colors[1].r = 0xff;
    s->format->palette->colors[1].g = 0xff;
    s->format->palette->colors[1].b = 0xff;
    s->format->palette->colors[1].a = 0xff;

    if (!SDL_LockSurface(s))
    {
        UBYTE * sp = ptr;
        UBYTE * dp = s->pixels;
        for (int v = 0; v < height; v++)
        {
            UBYTE bit = 0x80;
            for (int h = 0; h < width; h++)
            {
                if (*sp & bit)
                {
                    dp[h] = 0x1;
                }
                bit >>= 1;
                if (!bit)
                {
                    bit = 0x80;
                    sp++;
                }
            }
            dp += s->pitch;
        }
        SDL_UnlockSurface(s);
    }

    RUNLOGF("Saving \"%s\"...", fname);
    IMG_SavePNG(s, fname);
    SDL_FreeSurface(s);
}

// WIP
void save_png_5bpp_asset(char * fname, void * ptr, int width, int height)
{
    SDL_Surface * s = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    LoadRGB4(&vp_page, pagecolors, 32);
    SDL_SetPaletteColors(s->format->palette, vp_page.ColorMap->colors, 0, NUM_AMIGA_COLORS);

    if (!SDL_LockSurface(s))
    {
        UBYTE * sp = ptr;
        for (int p = 0; p < 5; p++)
        {
            UBYTE   bp = 1 << p;
            UBYTE * dp = s->pixels;
            for (int v = 0; v < height; v++)
            {
                UBYTE bit = 0x80;
                for (int h = 0; h < width; h++)
                {
                    if (*sp & bit)
                    {
                        dp[h] |= bp;
                    }
                    bit >>= 1;
                    if (!bit)
                    {
                        bit = 0x80;
                        sp++;
                    }
                }
                dp += s->pitch;
            }
        }
        SDL_UnlockSurface(s);
    }

    RUNLOGF("Saving \"%s\"...", fname);
    IMG_SavePNG(s, fname);
    SDL_FreeSurface(s);
}

#if 0
void load_bin_asset(char * fname, UBYTE * mem, int size)
{
    FILE * fp;
    CHECK(NULL != (fp = fopen(fname, "r")));
    if (fp)
    {
    }
}
#endif

// EOF
