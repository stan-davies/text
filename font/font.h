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

/*
 * Returns the height, in pixels, of the loaded font.
 */
float get_font_height(
        void
);

/*
 * Renders the given text at the given coordinates, wrapping to page width.
 */
int font_rend_text(
        char           *txt     ,       // Must be null-terminated.
        float           x       ,
        float           y
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
