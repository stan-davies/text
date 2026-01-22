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
        // Manage all this stuff someplace else?
        char *txt_typed_fore = NULL;
        char *txt_typed_aft  = NULL;
        sprint_txt(&txt_typed_fore, TXT_FORE);
        sprint_txt(&txt_typed_aft,  TXT_AFT);

        char *txt_add = calloc(get_maxkeys(), sizeof(char));

                // Need a better way of setting length.
        char *txt_display = calloc(128 + get_maxkeys(), sizeof(char));

        int input_ev;

        SDL_Event e;
        for (;;) {
                while (SDL_PollEvent(&e)) {
                        if (SDL_EVENT_QUIT == e.type) {
                                return;
                        } else if (SDL_EVENT_KEY_DOWN == e.type) {
                                if (SDLK_ESCAPE == e.key.key) {
                                        return;
                                }

                                input_ev = log_keyp(e.key.key);                
                                if (input_ev >= 0) {
                                        sprint_keybuf(&txt_add);
                                        if (KEYP_APPEND == input_ev) {
                                                sprint_txt(&txt_typed_fore, TXT_FORE);
                                        }
                                }
                                // Only update aft on cursor motion.
                        }
                }

                rendcl();
                sprintf(txt_display, "%s%s%s", txt_typed_fore, txt_add, txt_typed_aft);
                if (!font_rend_text(txt_display, 50, 50)) {
                        log_err("Error printing message.\n");
                        return;
                }
                push_rend();
        }

        free(txt_typed_fore);
        free(txt_typed_aft);
        free(txt_add);
        free(txt_display);
        txt_typed_fore = txt_typed_aft = txt_add = txt_display = NULL;
}
