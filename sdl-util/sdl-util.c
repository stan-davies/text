#include "sdl-util.h"

#include <stdio.h>

int init_sdl(
        SDL_Window    **win
) {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
                printf("Error initialising SDL.\n");
                return FALSE;
        }

        *win = SDL_CreateWindow("text", 800, 600, 0);

        if (!*win) {
                printf("Error creating window.\n");
                return FALSE;
        }

        return TRUE;
}

void end_sdl(
        SDL_Window    **win
) {
        SDL_DestroyWindow(*win);
        *win = NULL;
        SDL_Quit();
}
