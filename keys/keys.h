#ifndef KEYS_H
#define KEYS_H

#include "util.h"

void init_keys(
        void
);

void dest_keys(
        void
);

#define KEYP_INPUT              0       // Ordinary text input.
#define KEYP_APPEND             1       // Enter was hit, text was appended.
#define KEYP_ERROR             -1       // Something went wrong.
#define KEYP_NOTHING            2

int log_keyp(
        SDL_Scancode            k       ,
        int                     shift_d
);

int get_maxkeys(
        void
);

void sprint_keybuf(
        char                  **s
);

#endif
