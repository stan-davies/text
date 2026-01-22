#ifndef REND_H
#define REND_H

#include "util.h"

int init_rend(
        SDL_Window     *win
);

void dest_rend(
        void
);

void rendcl(
        void
);

void push_rend(
        void
);

int rend_tex(
        SDL_Texture    *tex     ,
        SDL_FRect       dst
);

int rend_srf(
        SDL_Surface    *srf     ,
        int             x       ,
        int             y
);

#endif
