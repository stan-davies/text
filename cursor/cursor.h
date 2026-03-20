#ifndef CURSOR_H
#define CURSOR_H

#include "util.h"

/*
 * Move cursor to given coordinates within screenspace.
 */
void cursor_place(
        float           x       ,
        float           y
);

/*
 * Draw cursor to the screen.
 */
int draw_cursor(
        Sint64          time
);

#endif
