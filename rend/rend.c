#include "rend.h"

static struct {
        int             I       ;
        SDL_Renderer   *r       ;

        struct {
                SDL_Texture    *tex     ;
                SDL_FRect       dst     ;
        } cache                         ;
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
        return TRUE;
}
        
void dest_rend(
        void
) {
        SDL_DestroyRenderer(rend.r);
        rend.r = NULL;
        rend.I = FALSE;

        SDL_DestroyTexture(rend.cache.tex);
        rend.cache.tex = NULL;
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

        return SDL_RenderTexture(rend.r, tex, NULL, &dst);
}

int rend_srf(
        SDL_Surface    *srf     ,
        int             x       ,
        int             y
) {
        if (!rend.I) {
                return FALSE;
        }

        SDL_Texture *tex = SDL_CreateTextureFromSurface(rend.r, srf);
        SDL_FRect    dst = { x, y, srf->w, srf->h };

        if (NULL == tex) {
                log_err("Failed to create texture from surface.");
                return FALSE;
        }

        int ret = rend_tex(tex, dst);

        SDL_DestroyTexture(rend.cache.tex);
        rend.cache.tex = tex;
        rend.cache.dst = dst;

//        SDL_DestroyTexture(tex);
//        tex = NULL;

        return ret;
}

int rend_cached_txt(
        void
) {
        if (NULL == rend.cache.tex) {
                log_err("No cached texture to render.");
                return FALSE;
        }

        return rend_tex(rend.cache.tex, rend.cache.dst);
}
