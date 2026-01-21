#include "cycl.h"

#include <stdlib.h>
#include <stdio.h>

#include "util.h"

#include "rend/rend.h"
#include "text/text.h"
#include "font/font.h"
#include "keys/keys.h"

void cycle(
        void
) {
        char *txt;
        sprint_txt(&txt);

        SDL_Event e;
        for (;;) {
                while (SDL_PollEvent(&e)) {
                        if (SDL_EVENT_QUIT == e.type) {
                                return;
                        } else if (SDL_EVENT_KEY_DOWN == e.type) {
                                if (SDLK_ESCAPE == e.key.key) {
                                        return;
                                }
                                
                                if (KEYP_APPEND == log_keyp(e.key.key)) {
                                        free(txt);
                                        txt = NULL;
                                        sprint_txt(&txt);
                                }
                        }
                }

                rendcl();
                if (!font_rend_text(txt, 50, 50)) {
                        log_err("Error printing message.\n");
                        return;
                }
                push_rend();
        }

        free(txt);
        txt = NULL;
}
