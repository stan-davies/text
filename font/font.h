#ifndef FONT_H
#define FONT_H

int init_font(
        void
);

void dest_font(
        void
);

// int open_font(path)          - returns ID for

int font_rend_text(
        char           *txt     ,       // Must be null-terminated.
        float           x       ,
        float           y
);

#endif
