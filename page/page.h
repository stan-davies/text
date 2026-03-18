#ifndef PAGE_H
#define PAGE_H

void init_page(
        void
);

void dest_page(
        void
);

int page_draw(
        void
);

int page_printline(
        char           *line
);

void page_scroll(
        float           by
);

#endif
