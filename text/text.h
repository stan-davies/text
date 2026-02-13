#ifndef TEXT_H
#define TEXT_H

/*
 * Initialise text manager.
 */
void init_txt_man(
        void
);

/*
 * Destroy text manager.
 */
void dest_txt_man(
        void
);

/*
 * Print currently held text to console.
 */
void print_txt(
        void
);

#define TXT_FORE                1       // 0b01
#define TXT_AFT                 2       // 0b10
#define TXT_BOTH                3       // 0b11

/*
 * Print currently held text to the string `s`. `bits` can be sent to above
 * macros in order for `s` to be populated with part before cursor, part after
 * cursor, or all of string held.
 */
void sprint_txt(
        char                  **s       ,
        int                     bits
);

/*
 * Returns total length of currently held text.
 */
int get_txtlen(
        void
);

/*
 * Appends given string to text in current cursor position.
 */
int txt_append(
        char                   *s
);

/*
 * Pops a character from the cursor position.
 */
int txt_pop(
        void
);

/*
 * Moves the cursor through the currently held text. Positive for forwards (or
 * right), negative for backwards (or left).
 */
int txt_move_cursor(
        int                     offset
);

#endif
