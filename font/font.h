#ifndef FONT_H
#define FONT_H

#define CURSOR_REDRAW   2

#include "util.h"

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

/*
 * Returns the height, in pixels, of the loaded font.
 */
float get_font_height(
        void
);

/*
 * Renders given string to a surface and returns it. All on one line, in black,
 * in default font.
 */
SDL_Surface *font_txt_to_srf(
        char           *txt 
);

/*
 * Renders the given text to the cache, wrapping to page width and scrolling to
 * accomodate the cursor and suchlike.
 */
int font_rend_text(
        char           *txt             // Must be null-terminated.
);

/*
 * Tell the font writer of the location of a click, so that when it next
 * renders the text it can check if the click was on the text, and thus
 * intended to move the cursor thereunto.
 */
void font_inform_click(
        float           x       ,
        float           y
);

#endif
