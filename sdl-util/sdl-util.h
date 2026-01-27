#ifndef SDL_INIT_H
#define SDL_INIT_H

#include "util.h"

/*
 * Initialises SDL and SDL_TTF, and creates a window.
 */
int init_sdl(
        SDL_Window    **win
);

/*
 * Ends SDL and SDL_TTF, and destroys the window.
 */
void end_sdl(
        SDL_Window    **win
);

#endif
