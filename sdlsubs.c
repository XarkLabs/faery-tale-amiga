/* sdl wrappers */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "amiga39.h"        // Xark: most AmigaOS includes (like "amiga39.pre")

#include "ftale.h"

#include <SDL.h>

BOOL sdl_quit;

char sdl_key;

struct SDL_Renderer * sdl_renderer;
struct SDL_Window *   sdl_window;

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

    fprintf(logfilep, "*** FTA/SDL2 Run Log - %s\n", time_stamp);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
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

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderSetScale(sdl_renderer, 1, 1);
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x40, 0x90, 255);
    SDL_RenderClear(sdl_renderer);
    SDL_RenderPresent(sdl_renderer);

    SDL_StartTextInput();

    return 0;
}

void sdl_endframe(void)
{
    sdl_pump();

    SDL_RenderPresent(sdl_renderer);
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
                if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2 ||
                    e.key.keysym.sym == SDLK_KP_ENTER)
                {
                    sdl_key = '\r';
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE || e.key.keysym.sym == SDLK_DELETE)
                {
                    sdl_key = '\b';
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    // TODO: ESC to quit is abrupt, but nice for development
                    RUNLOG("... ESC pressed");
                    sdl_quit = TRUE;
                }
                break;
            case SDL_TEXTINPUT:
                if (strlen(e.text.text) == 1)        // only single byte input
                {
                    sdl_key = e.text.text[0];
                }
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                break;
        }

        if (sdl_key != 0)
        {
            char kstr[2] = {sdl_key, 0};
            RUNLOGF("*SDL* keypress: %s [%d]", c_string(kstr, 1), sdl_key);
        }
    }

    if (sdl_quit)
    {
        RUNLOG("QUIT: exiting...");

        SDL_DestroyWindow(sdl_window);
        SDL_DestroyRenderer(sdl_renderer);
        SDL_Quit();

        exit(EXIT_SUCCESS);
    }
}
