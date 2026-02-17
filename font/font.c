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

#define SKIP_CLCK_POSITION      2

static struct {
        TTF_Font       *f       ;
        struct {
                int     w       ;
                int     h       ;
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
        const SDL_Color black = { 0, 0, 0, 255 };

        if (0 == strlen(txt)) {
                log_err("Trying to write an empty line. This will cause a segmentation fault.");
                return FALSE;
        }

        int ret = TRUE;
        SDL_Surface *srf = TTF_RenderText_Blended(font.f, txt, 0, black);
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

static int check_ln_click(
        float           x               ,
        float           y               ,
        int             ln_len          ,
        int             ln              ,
        int             chr_count
) {
        if (click.pos.y < y
         || click.pos.y > y + (float)((ln + 1) * font.char_size.h)) {
                return -1;
        }

        if (0 == ln_len) {
                printf("blank line\n");
        }

        if (click.pos.x < x) {
                printf("off the left of line %d, setting %d\n", ln, chr_count);
                // +1 if line is empty?
                return chr_count;
        }

        if (click.pos.x < x + (float)(ln_len * font.char_size.w)) {
                int tmp =  chr_count + (click.pos.x - x) / font.char_size.w;
                printf("within line %d, setting %d\n", ln, tmp);
                return tmp;
        }

        printf("off the right of line %d, setting %d\n", ln, chr_count + ln_len);
        return chr_count + ln_len;
}

int font_rend_text(
        char           *txt     ,       // Must be null-terminated.
        float           x       ,
        float           y
) {
        int ret = TRUE;
        int chars_per_line = 0.8f * SCREEN_WIDTH / (float)font.char_size.w;

        char *curr_line = calloc(chars_per_line + 1, sizeof(char));
        int lines       = 0;
        int more_lns    = TRUE;

        int chr_count =  0;
        int cursx     = -1;     // Cursor index.
        int clckx     = -1;     // Click index.

        float draw_y;

        init_writer(txt, chars_per_line);

        for (;;) {
                more_lns = writer_getline(&curr_line, &cursx);
                draw_y = y + (float)(lines * font.char_size.h);

                printf("line %d - %d\n", lines + 1, strlen(curr_line));

                if (cursx >= 0) {
                        cursor_place(x + (float)(cursx * font.char_size.w),
                                     draw_y);
                        cursx += chr_count;
                }

                if (TRUE == click.detect) {     // Takes 1,2,3.
                        clckx = check_ln_click(x, draw_y, strlen(curr_line),
                                                        lines, chr_count);
                        if (-1 != clckx) {
                                click.detect = SKIP_CLCK_POSITION;
                        }
                }

                if (strlen(curr_line) > 0 && !click.detect && !write_line(curr_line, x, draw_y)) {
                        log_err("Failed to print line.");
                        ret = FALSE;
                        click.detect = FALSE;
                        break;
                }

                if (!more_lns) {
                        break;
                }

                chr_count += strlen(curr_line);
                lines++;
        }

        switch (click.detect) {
        case SKIP_CLCK_POSITION:
                flush_keybuf();
                txt_move_cursor(clckx - cursx);
                // No break.
        case TRUE:
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
        click.pos.x = x;
        click.pos.y = y;
        click.detect = TRUE;
}
