#ifndef FONT_H
#define FONT_H

/*
 * Intialises the font handler.
 */
int init_font(
        void
);

/*
 * Destroys the font handler.
 */
void dest_font(
        void
);

// int open_font(path)          - returns ID for

/*
 * Renders the given text at the given coordinates, wrapping to page width.
 */
int font_rend_text(
        char           *txt     ,       // Must be null-terminated.
        float           x       ,
        float           y
);

#endif
