#ifndef PAGE_H
#define PAGE_H

/*
 * Initialises the page.
 */
void init_page(
        void
);

/*
 * Destroys the page.
 */
void dest_page(
        void
);

/*
 * Draws the page to the current frame.
 */
int page_draw(
        void
);

/*
 * Empties the page so that it can be redrawn.
 */
void page_clear(
        void
);

/*
 * Appends the given line of text to the end of page.
 */
int page_printline(
        char           *line
);

/*
 * Scrolls the page content up and down.
 */
void page_scroll(
        float           by
);

void page_place_cursor(
        int             cx      ,       // x-pos of character to place at.
        int             cy              // y-pos of character to place at.
                                // Both are scaled to character size (so px).
);

#endif
