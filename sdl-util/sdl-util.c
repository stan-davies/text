#include "sdl-util.h"

#include <stdio.h>

#include "font/font.h"

int init_sdl(
        SDL_Window    **win
) {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
                log_err("Error initialising SDL.");
                return FALSE;
        }

        *win = SDL_CreateWindow("text", SCREEN_WIDTH, SCREEN_HEIGHT,
                                                SDL_WINDOW_INPUT_FOCUS);

        if (!*win) {
                log_err("Error creating window.");
                // END SDL?
                return FALSE;
        }

        if (!init_font()) {
                log_err("Error initialising SDL-ttf.");
                // END SDL + DESTROY WINDOW?
                return FALSE;
        }

        return TRUE;
}

void end_sdl(
        SDL_Window    **win
) {
        dest_font();
        SDL_DestroyWindow(*win);
        *win = NULL;
        SDL_Quit();
}
