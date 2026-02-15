#include "cursor.h"

#include "util.h"
#include "rend/rend.h"
#include "font/font.h"

static struct {
        float           x       ;
        float           y       ;
} cursor = {
        .x      =       0.f     ,
        .y      =       0.f
};

void cursor_place(
        float           x       ,
        float           y
) {
        cursor.x = x;        
        cursor.y = y;
}

int draw_cursor(
        void
) {
        static SDL_Color col = { 32, 33, 247, 255 };
        SDL_FRect cur = {
                cursor.x,
                cursor.y + 2.f,
                2.f, get_font_height()
        };
        return rend_rct(cur, col);
}
