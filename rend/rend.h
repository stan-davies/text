#ifndef REND_H
#define REND_H

#include "util.h"

void init_rend(
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

#endif
