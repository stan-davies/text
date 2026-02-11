#include "sdl-util.h"

#include <stdio.h>

#include "font/font.h"

static int ttf_up = FALSE;

int init_sdl(
        SDL_Window    **win
) {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
                log_err("Error initialising SDL.");
                return FALSE;
        }
        log_msg("  Initialised SDL.");

        *win = SDL_CreateWindow("text", SCREEN_WIDTH, SCREEN_HEIGHT,
                                                SDL_WINDOW_INPUT_FOCUS);

        if (!*win) {
                log_err("Error creating window.");
                end_sdl(win);
                return FALSE;
        }

        if (!init_font()) {
                log_err("Error initialising SDL-ttf.");
                end_sdl(win);
                return FALSE;
        }
        ttf_up = TRUE;
        log_msg("  Initialised SDL-ttf.");

        return TRUE;
}

void end_sdl(
        SDL_Window    **win
) {
        if (ttf_up) {
                dest_font();
                log_msg("  Ended SDL-ttf.");
        }
        if (*win != NULL) {
                SDL_DestroyWindow(*win);
                *win = NULL;
        }
        SDL_Quit();
        log_msg("  Ended SDL.");
}
