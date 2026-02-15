#include "cursor.h"

#include "util.h"
#include "rend/rend.h"
#include "font/font.h"

#define FLASH_INTERVAL  800     // Milliseconds.

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
        Uint64          time
) {
        static SDL_Color col = { 32, 33, 247, 255 };
        static Uint64 change = 0;
        static int vis = TRUE;

        if (time - change >= FLASH_INTERVAL) {
                change = time;
                vis = !vis;
        }

        if (!vis) {
                return TRUE;
        }

        SDL_FRect cur = {
                cursor.x,
                cursor.y + 2.f,
                2.f, get_font_height()
        };
        return rend_rct(cur, col);
}
