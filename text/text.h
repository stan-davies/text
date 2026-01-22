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

#define TXT_FORE                1       // 0b01
#define TXT_AFT                 2       // 0b10
#define TXT_BOTH                3       // 0b11

void sprint_txt(
        char                  **s       ,
        int                     bits
);

int append_txt(
        char                   *s
);

int move_cursor(
        int                     offset
);

#endif
