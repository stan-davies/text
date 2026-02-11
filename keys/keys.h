#ifndef KEYS_H
#define KEYS_H

#include "util.h"

/*
 * Initialises the keyboard handler.
 */
void init_keys(
        void
);

/*
 * Destroys the keyboard handler.
 */
void dest_keys(
        void
);

#define KEYP_INPUT              0       // Ordinary text input.
#define KEYP_APPEND             1       // Enter was hit, text was appended.
#define KEYP_ERROR             -1       // Something went wrong.
#define KEYP_NOTHING            2

/*
 * Log a keypress of the given scancode. Returns one of above macros for the
 * effect on the text currently being edited.
 */
int log_keyp(
        SDL_Scancode            k       ,
        int                     shift_d
);

/*
 * Returns maximum length of string the key logger can hold at any one time.
 */
int get_maxkeys(
        void
);

/*
 * Prints the buffer of the key logger to the given string.
 */
void sprint_keybuf(
        char                  **s
);

/*
 * Empties the buffer of the key logger, appending all typed characters to the
 * permenant buffer in `text`.
 */
int flush_keybuf(
        void
);

#endif
