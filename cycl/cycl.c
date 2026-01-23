#include "cycl.h"

#include <stdlib.h>
#include <stdio.h>

#include "util.h"

#include "rend/rend.h"
#include "text/text.h"
#include "font/font.h"
#include "keys/keys.h"

static struct {
        char           *typed_fore      ;
        char           *typed_aft       ;
        char           *typing          ;
        
        char           *display         ;
} txt = {               // All the bits of text currently being shown.
        .typed_fore     =       NULL    ,
        .typed_aft      =       NULL    ,
        .typing         =       NULL    ,
        .display        =       NULL
};

void init_cycle(
        void
) {
        // Manage all this stuff someplace else?
        sprint_txt(&txt.typed_fore, TXT_FORE);
        sprint_txt(&txt.typed_aft,  TXT_AFT);

        txt.typing = calloc(get_maxkeys(), sizeof(char));
        txt.display = calloc(get_txtlen() + get_maxkeys(), sizeof(char));
}

void end_cycle(
        void
) {
        free(txt.typed_fore);
        free(txt.typed_aft);
        free(txt.typing);
        free(txt.display);
        txt.typed_fore = txt.typed_aft = txt.typing = txt.display = NULL;
}

void cycle(
        void
) {
        SDL_Event e;
        for (;;) {
                while (SDL_PollEvent(&e)) {
                        if (SDL_EVENT_QUIT == e.type) {
                                return;
                        } else if (SDL_EVENT_KEY_DOWN == e.type) {
                                if (SDLK_ESCAPE == e.key.key) {
                                        return;
                                }

                                switch (log_keyp(e.key.scancode, e.key.mod == SDL_KMOD_LSHIFT)) {
                                case KEYP_NOTHING:
                                        break;
                                case KEYP_APPEND:
                                        txt.display = realloc(txt.display, get_txtlen() + get_maxkeys() * sizeof(char));
                                        sprint_txt(&txt.typed_fore, TXT_FORE);
                                        // No break.
                                case KEYP_INPUT:
                                        sprint_keybuf(&txt.typing);
                                        break;
                                default:
                                        log_err("Problem taking input.");
                                        return;
                                }
                                // Only update txt.typed_aft on cursor motion.
                        }
                }

                rendcl();
                sprintf(txt.display, "%s%s%s", txt.typed_fore, txt.typing, txt.typed_aft);
                if (!font_rend_text(txt.display, 50, 50)) {
                        log_err("Error printing message.\n");
                        return;
                }
                push_rend();
        }
}
