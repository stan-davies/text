#include "page.h"

#include <stdlib.h>

#include "util.h"
#include "rend/rend.h"
#include "font/font.h"
#include "cursor/cursor.h"

// Going for the really tall texture approach, may still need resizing.

static struct {
        SDL_Texture    *cache   ;
        struct float2   pos     ;       // In screenspace.
        struct float2   dim     ;       // Of texture.
        struct float2   vis     ;       // Dimensions visible (given to `dst`).

        int             lines   ;

        float           scroll  ;
} page  = {
        .pos    = {
                .x      =       0.1f * SCREEN_WIDTH     ,
                .y      =       0.1f * SCREEN_HEIGHT
        }       ,
        .dim    = {
                .x      =       0.8f * SCREEN_WIDTH     ,
                .y      =       2.f  * SCREEN_HEIGHT    // More?
        }       ,
        .vis    = {
                .x      =       0.8f * SCREEN_WIDTH     ,
                .y      =       0.8f * SCREEN_HEIGHT
        }       ,
        .lines  =       0                               ,
        .scroll =       0.f
};

// Kind of want to store the text in here almost, but then only operate on it
// using the text functions?

void init_page(
        void
) {
        page.cache  = rend_create_tex(SDL_TEXTUREACCESS_TARGET, 
                                                page.dim.x, page.dim.y);

        log_msg("  Initialised page.");
}

void dest_page(
        void
) {
        rend_dest_tex(&page.cache);
        log_msg("  Ended page manager.");
}

int page_draw(
        void
) {
        SDL_FRect src = { 0, page.scroll, page.vis.x, page.vis.y - page.scroll };
        SDL_FRect dst = { page.pos.x, page.pos.y, page.vis.x, page.vis.y - page.scroll };
        return rend_tex(page.cache, &src, &dst);
}

void page_clear(
        void
) {
        page.lines = 0;
        clear_tex(page.cache);
}

int page_printline(
        char           *line
) {
        // store line, another function to reset it every now and then
        // ^ What the hell does this mean?

        /*   If lines are being stored, then perhaps do a 'editing line n' then
         *   redo the alignment for lines m such that n - 1 ≤ m. Could also do
         *   a kind of separating words into symbols. This is sounding like a
         *   really major rework.
         */

        if (0 == strlen(line)) {
                page.lines++;
                return TRUE;
        }

        SDL_Surface *s = font_txt_to_srf(line);
        SDL_FRect dst  = { 0, page.lines * s->h, s->w, s->h };
                // ^ Within `page.cache`.

        int ret = rend_srf_to_tex(page.cache, s, NULL, &dst);
        page.lines++;

        SDL_DestroySurface(s);
        s = NULL;

        return ret;
}

void page_scroll(
        float           by
) {
        page.scroll += by;

        if (page.scroll < 0.f) {
                page.scroll = 0.f;
        } else if (page.scroll > page.lines * 20.f) {
                page.scroll = page.lines * 20.f;
        }

        // Alternative, original upper limit that might come in handy (?).
//        } else if (page.scroll > page.dim.y - page.vis.y) {
//                page.scroll = page.dim.y - page.vis.y;
}

void page_place_cursor(
        int             cx      ,
        int             cy
) {
        float x = page.pos.x + (float)cx;
        float y = page.pos.y + (float)cy - page.scroll;

        cursor_place(x, y);
}
