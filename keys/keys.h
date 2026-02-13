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

#define KEYP_ERROR             -1       // Something went wrong.
#define KEYP_INPUT              0       // Ordinary text input.
#define KEYP_APPEND             1       // Enter was hit, text was appended.
#define KEYP_NOTHING            2       // Some kind of special key that
                                        // warrants no action.
#define KEYP_BACKSPACE          3       // A character has been popped from
                                        // behind the cursor.

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
 * Prints the buffer of the key logger to the given string. Returns number of
 * characters written to string.
 */
int sprint_keybuf(
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
