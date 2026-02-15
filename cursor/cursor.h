#ifndef CURSOR_H
#define CURSOR_H

#include "util.h"

void cursor_place(
        float           x       ,
        float           y
);

int draw_cursor(
        Uint64          time
);

#endif
