#include "font.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "rend/rend.h"
#include "writer/writer.h"
#include "cursor/cursor.h"
#include "text/text.h"
#include "keys/keys.h"
#include "page/page.h"

#define SKIP_CLCK_POSITION      2

static struct {
        TTF_Font       *f       ;
        struct {
                int     w       ;       // Width of one character in px.
                int     h       ;       // Height of one character in px.
        } char_size             ;
} font;

static struct {
        struct {
                float   x       ;
                float   y       ;
        } pos;

        int             detect  ;
} click;

static int write_line(
        char           *txt     ,
        float           x       ,
        float           y
) {
        if (0 == strlen(txt)) {
                log_err("Trying to write an empty line. This will cause a"
                        "segmentation fault.");
                return FALSE;
        }

        int ret = TRUE;
        SDL_Surface *srf = font_txt_to_srf(txt);
        if (!rend_srf(srf, x, y, TRUE)) {
                log_err("Failed to print a line... =/");
                ret = FALSE;
        }
        SDL_DestroySurface(srf);
        srf = NULL;
        return ret;
}

int init_font(
        void
) {
        if (!TTF_Init()) {
                log_err("Error initialising SDL-ttf.\n");
                return FALSE;
        }

        font.f = TTF_OpenFont("assets/font.ttf", 24);
        if (!font.f) {
                log_err("Error loading font.\n");
                // quit TTF?
                return FALSE;
        }
        int single;
        TTF_GetStringSize(font.f, "A", 1, &single, &font.char_size.h);
        TTF_GetStringSize(font.f, "AA", 2, &font.char_size.w, NULL);
        font.char_size.w -= single;

        return TRUE;
}

void dest_font(
        void
) {
        TTF_CloseFont(font.f);
        font.f = NULL;
        TTF_Quit();
}

float get_font_height(
        void
) {
        return font.char_size.h;
}

SDL_Surface *font_txt_to_srf(
        char           *txt
) {
        const SDL_Color black = { 0, 0, 0, 255 };
        return TTF_RenderText_Blended(font.f, txt, 0, black);
}

static int check_ln_click(
        float           x               ,
        float           y               ,
        int             ln_len          ,
        int             chr_count
) {
        if (click.pos.y < y
         || click.pos.y > y + (float)font.char_size.h) {
                return -1;
        }

        if (click.pos.x < x) {
                return chr_count;
        }

        if (click.pos.x < x + (float)(ln_len * font.char_size.w)) {
                return chr_count + (click.pos.x - x) / font.char_size.w;
        }

        return chr_count + ln_len;
}

// Starting to hate how big this function is.
int font_rend_text(
        char           *txt             // Must be null-terminated.
) {
        static int scroll_pos = 0;
        
        int ret = TRUE;

        int chars_per_line = CACHE_WIDTH / (float)font.char_size.w;
        int end_line = scroll_pos + CACHE_HEIGHT / (float)font.char_size.h;

        char *curr_line = calloc(chars_per_line + 1, sizeof(char));
        int lines       = 0;
        int more_lns    = TRUE;

        int chr_count =  0;
                // Really okay for these to be -1?
        int cursx     = -1;     // Cursor index.
        int clckx     = -1;     // Click index.

        float draw_y;   // In cache space.

        int x, y;

        page_clear();
        init_writer(txt, chars_per_line);
        
        for (;;) {
                more_lns = writer_getline(&curr_line, &cursx);
                draw_y = (float)((lines - scroll_pos) * font.char_size.h);

                if (cursx >= 0) {
                        // This could be a function (if cursx were global...)
//                        x = (float)(cursx * font.char_size.w);
//                        y = draw_y;
//                        cstoss(&x, &y);
//                        cursor_place(x, y);
                        page_place_cursor(
                                cursx * font.char_size.w,
                                lines * font.char_size.h
                        );
                        cursx = -chr_count - cursx;
                }

                if (TRUE == click.detect) {     // Takes 0,1,2.
                        // This could probably be a function...?
                        clckx = check_ln_click(0, draw_y,
                                                strlen(curr_line), chr_count);
                        if (-1 != clckx) {
                                click.detect = SKIP_CLCK_POSITION;
                        }
                }

        // First condition is really on whether to run `page_printline`.
                if (!click.detect && !page_printline(curr_line)) {
                        // This could totally be a function.
                        log_err("Failed to print line.");
                        ret = FALSE;
                        click.detect = FALSE;
                        break;
                }

                if (!more_lns) {
                        break;
                }

                chr_count += strlen(curr_line) + 1; // +1 for '\n'
                lines++;

                // I guess this stuff could be a function?
                        // Cursor unplaced in visible region.
                if (lines >= end_line && -1 == cursx) {
                        ret = CURSOR_REDRAW;
                        scroll_pos++;
                } else if (lines == scroll_pos && cursx < -1) {
                // This doesn't seem to work. Or actually does...?
                        ret = CURSOR_REDRAW;
                        scroll_pos--;
                }
        }

        switch (click.detect) {
        case SKIP_CLCK_POSITION:        // Was a click and new position found.
                flush_keybuf();
                txt_move_cursor(clckx + cursx);
                // No break.
        case TRUE:                      // Was a click and no new position found(?).
                click.detect = FALSE;
                ret = CURSOR_REDRAW;
                break;
        default:
                break;
        }

        dest_writer();
        free(curr_line);
        curr_line = NULL;

        return ret;
}

void font_inform_click(
        float           x       ,
        float           y
) {
        sstocs(&x, &y);
        click.pos.x = x;
        click.pos.y = y;
        click.detect = TRUE;
}
