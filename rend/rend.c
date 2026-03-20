#include "rend.h"

static struct {
        int             I       ;
        SDL_Renderer   *r       ;

        struct {
                SDL_Texture    *tex     ;
                SDL_FRect       dst     ;
        } cache                         ;
} rend = {
        .I              =       FALSE   ,
        .r              =       NULL    ,
        .cache.dst      =       {
                .x      =       (SCREEN_WIDTH - CACHE_WIDTH) / 2        ,
                .y      =       (SCREEN_HEIGHT - CACHE_HEIGHT) / 2      ,
                .w      =       CACHE_WIDTH                             ,
                .h      =       CACHE_HEIGHT
        }
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
                SDL_TEXTUREACCESS_TARGET, CACHE_WIDTH, CACHE_HEIGHT);

        log_msg("  Initialised renderer.");

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

        log_msg("  Ended renderer.");
}

void cstoss(
        int            *x       ,
        int            *y
) {
        *x += rend.cache.dst.x;
        *y += rend.cache.dst.y;
}

void sstocs(
        float          *x       ,
        float          *y
) {
        *x -= rend.cache.dst.x;
        if (*x < 0) {
                *x = 0;
        } else if (*x > rend.cache.dst.w) {
                *x = rend.cache.dst.w;
        }
        *y -= rend.cache.dst.y;
        if (*y < 0) {
                *y = 0;
        } else if (*y > rend.cache.dst.h) {
                *y = rend.cache.dst.h;
        }
}

void clear_frame(
        void
) {
        rendcl();
}

void flush_frame(
        void
) {
        SDL_RenderPresent(rend.r);
}

void clear_cache(
        void
) {
        clear_tex(rend.cache.tex);
}

void clear_tex(
        SDL_Texture    *tex
) {
        if (NULL == tex) {
                return;
        }
        SDL_SetRenderTarget(rend.r, tex);
        rendcl();
        SDL_SetRenderTarget(rend.r, NULL);
}

int rend_cache(
        void
) {
        if (!rend_tex(rend.cache.tex, NULL, &rend.cache.dst)) {
                log_err("Failed to render cached texture.");
                return FALSE;
        }
        return TRUE;
}

int rend_tex(
        SDL_Texture    *tex     ,
        SDL_FRect      *src     ,
        SDL_FRect      *dst
) {
        if (!rend.I) {
                return FALSE;
        }

        return SDL_RenderTexture(rend.r, tex, src, dst);
}

int rend_srf_to_tex(
        SDL_Texture    *canvas  ,
        SDL_Surface    *print   ,
        SDL_FRect      *src     ,
        SDL_FRect      *dst
) {
        if (!rend.I || NULL == print || NULL == canvas) {
                return FALSE;
        }

        SDL_Texture *tex = SDL_CreateTextureFromSurface(rend.r, print);
        if (NULL == tex) {
                log_err("Could not create texture from surface.");
                return FALSE;
        }

        SDL_SetRenderTarget(rend.r, canvas);
        int ret = rend_tex(tex, src, dst);
        SDL_SetRenderTarget(rend.r, NULL);

        SDL_DestroyTexture(tex);
        tex = NULL;
        return ret;
}

int rend_tex_to_tex(
        SDL_Texture    *canvas  ,
        SDL_Texture    *print   ,
        SDL_FRect      *src     ,
        SDL_FRect      *dst
) {
        if (!rend.I || NULL == print || NULL == canvas) {
                return FALSE;
        }

        SDL_SetRenderTarget(rend.r, canvas);

        int ret = rend_tex(print, src, dst);

        SDL_SetRenderTarget(rend.r, NULL);

        return ret;
}

int rend_srf(
        SDL_Surface    *srf     ,
        int             x       ,
        int             y       ,
        int             to_c
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

        if (to_c) {
                SDL_SetRenderTarget(rend.r, rend.cache.tex);
        }

        int ret = rend_tex(tex, NULL, &dst);

        if (to_c) {
                SDL_SetRenderTarget(rend.r, NULL);
        }

        SDL_DestroyTexture(tex);
        tex = NULL;

        return ret;
}

int rend_rct(
        SDL_FRect       rct     ,
        SDL_Color       c
) {
        if (!rend.I) {
                return FALSE;
        }

        SDL_SetRenderDrawColor(rend.r, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(rend.r, &rct);
        return TRUE;
}

SDL_Texture *rend_create_tex(
        SDL_TextureAccess       access  ,
        int             x       ,
        int             y
) {
        SDL_Texture *t = SDL_CreateTexture(rend.r, SDL_PIXELFORMAT_RGBA8888,
                                                                access, x, y);
        return t;
}

void rend_dest_tex(
        SDL_Texture   **tex
) {
        SDL_DestroyTexture(*tex);
        *tex = NULL;
}
