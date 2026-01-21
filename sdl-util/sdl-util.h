#ifndef SDL_INIT_H
#define SDL_INIT_H

#include "util.h"

int init_sdl(
        SDL_Window    **win
);

void end_sdl(
        SDL_Window    **win
);

#endif
