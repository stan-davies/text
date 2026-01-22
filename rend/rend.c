#include "rend.h"

static struct {
        int             I       ;
        SDL_Renderer   *r       ;
} rend = {
        .I      =       FALSE   ,
        .r      =       NULL
};

int init_rend(
        SDL_Window     *win
) {
        rend.r = SDL_CreateRenderer(win, NULL);
        rend.I = TRUE;

        if (!SDL_SetRenderVSync(rend.r, 1)) {
                log_err("Failed to enable VSync");
                return FALSE;
        }
}
        
void dest_rend(
        void
) {
        SDL_DestroyRenderer(rend.r);
        rend.r = NULL;
        rend.I = FALSE;
}

void rendcl(
        void
) {
        SDL_SetRenderDrawColor(rend.r, 255, 255, 255, 255);
        SDL_RenderClear(rend.r);
}

void push_rend(
        void
) {
        SDL_RenderPresent(rend.r);
}

int rend_tex(
        SDL_Texture    *tex     ,
        SDL_FRect       dst
) {
        if (!rend.I) {
                return FALSE;
        }

        SDL_RenderTexture(rend.r, tex, NULL, &dst);
        return TRUE;
}

int rend_srf(
        SDL_Surface    *srf     ,
        int             x       ,
        int             y
) {
        SDL_Texture *tex = SDL_CreateTextureFromSurface(rend.r, srf);
        SDL_FRect    dst = { x, y, srf->w, srf->h };

        return rend_tex(tex, dst);
}
