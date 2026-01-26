#include "font.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "rend/rend.h"

static struct {
        TTF_Font       *f       ;
} font;

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
        if (!rend_srf(srf, x, y)) {
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

        return TRUE;
}

void dest_font(
        void
) {
        TTF_CloseFont(font.f);
        font.f = NULL;
        TTF_Quit();
}

int font_rend_text(
        char           *txt     ,       // Must be null-terminated.
        float           x       ,
        float           y
) {
        int char_width, char_height;
        TTF_GetStringSize(font.f, "A", 1, &char_width, &char_height);

        int chars_per_line = 0.9f * SCREEN_WIDTH / char_width;        
        char *curr_line = calloc(chars_per_line + 1, sizeof(char));

        char *c = txt;
        int i = 0;
        int lines = 0;
        int run = TRUE;
        int ret = TRUE;

        while (run) {
                if ('\0' == *c) {
                        run = FALSE;
                } else if ('\n' == *c) {
                        c++;
                        if (0 == i) {
                                goto linefeed;
                        }
                } else if (i < chars_per_line) {
                        curr_line[i++] = *c++;
                        continue;
                }
                curr_line[i] = '\0';
                if (!write_line(curr_line, x, y + (float)(lines * char_height))) {
                        ret = FALSE;
                        break;
                }
linefeed:
                i = 0;
                lines++;
        }

        free(curr_line);
        curr_line = NULL;
        return ret;
}
