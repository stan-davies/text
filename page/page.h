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

#endif
