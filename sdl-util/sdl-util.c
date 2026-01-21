#include "sdl-util.h"

#include <stdio.h>

#include "font/font.h"

int init_sdl(
        SDL_Window    **win
) {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
                printf("Error initialising SDL.\n");
                return FALSE;
        }

        *win = SDL_CreateWindow("text", 800, 600, SDL_WINDOW_INPUT_FOCUS);

        if (!*win) {
                printf("Error creating window.\n");
                // END SDL?
                return FALSE;
        }

        if (!init_font()) {
                printf("Error initialising SDL-ttf.\n");
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
