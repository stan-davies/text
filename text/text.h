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

void print_txt(
        void
);

void sprint_txt(
        char                  **s               // Should be unallocated.
);

int append_txt(
        char                   *s
);

int move_cursor(
        int                     offset
);

#endif
