#include "rend.h"

static struct {
        int             I       ;
        SDL_Renderer   *r       ;
} rend = {
        .I      =       FALSE   ,
        .r      =       NULL
};

void init_rend(
        SDL_Window     *win
) {
        rend.r = SDL_CreateRenderer(win, NULL);
        rend.I = TRUE;
}
        
void dest_rend(
        void
) {
        SDL_DestroyRenderer(rend.r);
        rend.r = NULL;
        rend.I = FALSE;
}
