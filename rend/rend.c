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

static void rendcl(
        void
) {
        SDL_SetRenderDrawColor(rend.r, 255, 255, 255, 255);
        SDL_RenderClear(rend.r);
}

int init_rend(
        SDL_Window     *win
) {
        rend.r = SDL_CreateRenderer(win, NULL);
        rend.I = TRUE;

        if (!SDL_SetRenderVSync(rend.r, 1)) {
                log_err("Failed to enable VSync");
                return FALSE;
        }
        
        rend.cache.tex = SDL_CreateTexture(rend.r, SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_SetRenderTarget(rend.r, rend.cache.tex);

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

void clear_cache(
        void
) {
        rendcl();
}

int rend_cache(
        void
) {
        SDL_SetRenderTarget(rend.r, NULL);

        rendcl();

        SDL_FRect dst = { 0, 0, rend.cache.tex->w, rend.cache.tex->h };
        if (!rend_tex(rend.cache.tex, dst)) {
                log_err("Failed to render cached texture.");
                return FALSE;
        }

        SDL_RenderPresent(rend.r);

        SDL_SetRenderTarget(rend.r, rend.cache.tex);

        return TRUE;
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
        
        if (ret) {
                log_msg("texture drawn");
        }

        SDL_DestroyTexture(tex);
        tex = NULL;

        return ret;
}
