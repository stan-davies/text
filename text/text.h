#ifndef TEXT_H
#define TEXT_H

/*
 * Initialise text manager.
 */
void init_text_man(
        void
);

/*
 * Destroy text manager.
 */
void dest_text_man(
        void
);

void print_txt(
        void
);

int append_txt(
        char                   *s
);

int move_cursor(
        int                     offset
);

#endif
