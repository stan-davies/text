#include "font.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "rend/rend.h"

static struct {
        TTF_Font       *f       ;
} font;

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
        const SDL_Color black = { 0, 0, 0, 255 };

        int char_width, char_height;
        TTF_GetStringSize(font.f, "A", 1, &char_width, &char_height);
        int line_width = 0.9f * SCREEN_WIDTH;

        int chars_per_line = line_width / char_width;        
        char *curr_line = calloc(chars_per_line + 1, sizeof(char));

        char *c = txt;
        int i = 0;
        int lines = 0;
        int ret = TRUE;
        SDL_Surface *srf;
        int run = TRUE;

        while (run) {
                if ('\0' == *c) {
                        run = FALSE;
                } else if (i < chars_per_line && '\0' != *c) {
                        curr_line[i++] = *c++;
                        continue;
                }
                curr_line[i] = '\0';
                srf = TTF_RenderText_Blended(font.f, curr_line, 0, black);
                if (!rend_srf(srf, x, y + (float)(lines * char_height))) {
                        log_err("Failed to print a line... =/");
                        ret = FALSE;
                } else {
                        log_msg("printed '%s' at %f %f", curr_line, x, y + (float)(lines * char_height));
                }
                SDL_DestroySurface(srf);
                srf = NULL;

                i = 0;
                lines++;
        }

        return ret;
}
