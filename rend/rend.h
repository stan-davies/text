#ifndef REND_H
#define REND_H

#include "util.h"

/*
 * Initialises the renderer.
 */
int init_rend(
        SDL_Window     *win
);

/*
 * Destroys the renderer.
 */
void dest_rend(
        void
);

/*
 * Clears the render context ready for next frame.
 */
void rendcl(
        void
);

/*
 * Flushes current frames renderings to the window. Should be called after
 * `rendcl` and other rendering calls.
 */
void push_rend(
        void
);

/*
 * Renders the given texture in the given subsection of the window.
 */
int rend_tex(
        SDL_Texture    *tex     ,
        SDL_FRect       dst
);

/*
 * Renders the given surface in the given coordinates within the window.
 */
int rend_srf(
        SDL_Surface    *srf     ,
        int             x       ,
        int             y
);

#endif
