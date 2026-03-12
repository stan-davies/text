#ifndef REND_H
#define REND_H

#include "util.h"

#define CACHE_WIDTH     0.8f * SCREEN_WIDTH
#define CACHE_HEIGHT    0.8f * SCREEN_HEIGHT

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
 * Converts cache space coordinates to screen space coordinates.
 */
void cstoss(
        int            *x       ,
        int            *y
);

/*
 * Converts screen space coordinates to cache space coordinates, limiting to
 * bounds.
 */
void sstocs(
        float          *x       ,
        float          *y
);


/*
 * Clears the cached texture so that it can be redrawn.
 */
void clear_cache(
        void
);

/*
 * Clears the render frame for redrawing.
 */
void clear_frame(
        void
);

/*
 * Flushes the render frame to the screen.
 */
void flush_frame(
        void
);

/*
 * Renders cached texture to window.
 */
int rend_cache(
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
        int             y       ,
        int             to_c            // Render to cache.
);

/*
 * Renders the given rectangle in the given colour.
 */
int rend_rct(
        SDL_FRect       rct     ,
        SDL_Color       c
);

#endif
