#include "font.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

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
        SDL_Surface *srf = TTF_RenderText_Solid(font.f, txt, 0, black);
        int ret = rend_srf(srf, x, y);
        SDL_DestroySurface(srf);
        srf = NULL;

        return ret;
}
