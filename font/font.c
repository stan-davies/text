#include "font.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "rend/rend.h"
#include "writer/writer.h"
#include "cursor/cursor.h"

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
                printf("Error initialising SDL-ttf.\n");
                return FALSE;
        }

        font.f = TTF_OpenFont("assets/font.ttf", 24);
        if (!font.f) {
                printf("Error loading font.\n");
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

int font_rend_text(
        char           *txt     ,       // Must be null-terminated.
        float           x       ,
        float           y
) {
        int ret = TRUE;
        int chars_per_line = 0.8f * SCREEN_WIDTH / (float)font.char_size.w;

        char *curr_line = calloc(chars_per_line + 1, sizeof(char));
        int lines = 0;
        int more_lns = TRUE;

        int cursx = -1;
        int clckx = -1;

        float draw_y;

        init_writer(txt, chars_per_line);

        for (;;) {
                more_lns = writer_getline(&curr_line, &cursx);
                if (0 == strlen(curr_line)) {
                        goto loop_end;
                }

                draw_y = y + (float)(lines * font.char_size.h);

                if (cursx >= 0) {
                        cursor_place(x + (float)(cursx * font.char_size.w),
                                     draw_y);
                        cursx *= -1;
                }

                if (!write_line(curr_line, x, draw_y)) {
                        log_err("Failed to print line.");
                        ret = FALSE;
                        break;
                }

                if (click.detect
                 && draw_y < click.pos.y
                 && y + (float)((lines + 1) * font.char_size.h) > click.pos.y
                 && x < click.pos.x
                 && x + (float)(strlen(curr_line) * font.char_size.w) > click.pos.x) {
                        clckx = click.pos.x / font.char_size.w;
                        printf("on %d\n", clckx);
                        click.detect = FALSE;
                }

loop_end:
                if (!more_lns) {
                        break;
                }

                lines++;
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
