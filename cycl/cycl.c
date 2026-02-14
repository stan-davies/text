#include "cycl.h"

#include <stdlib.h>
#include <stdio.h>

#include "util.h"

#include "rend/rend.h"
#include "text/text.h"
#include "font/font.h"
#include "keys/keys.h"
#include "cursor/cursor.h"

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

static Uint64 press_time = 0;
static int could_append = FALSE;

void init_cycle(
        void
) {
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

static void do_append(
        void
) {
        flush_keybuf();

        txt.display = realloc(txt.display,
                        (get_txtlen() + get_maxkeys()) * sizeof(char));
        if (NULL == txt.display) {
                log_err("realloc to null in `do_append`");
        }
        sprint_txt(&txt.typed_fore, TXT_FORE);
        sprint_keybuf(&txt.typing);

        could_append = FALSE;
}

static int reg_keyb_input(
        SDL_Event               e
) {
        switch (log_keyp(e.key.scancode, e.key.mod == SDL_KMOD_LSHIFT)) {
        case KEYP_NOTHING:
                break;
        case KEYP_APPEND:
                do_append();
                break;
        case KEYP_INPUT:
                could_append = sprint_keybuf(&txt.typing) > 0;
                break;
        case KEYP_BACKSPACE:
                if (!txt_pop()) {
                        log_err("Failed to pop character.");
                        return FALSE;
                }
                sprint_txt(&txt.typed_fore, TXT_FORE);
                break;
        default:
                log_err("Problem taking input.");
                return FALSE;
        }

        return TRUE;
}

void cycle(
        void
) {
        SDL_Event e;
        Uint64 curr_time;
        int input = TRUE;
        for (;;) {
                curr_time = SDL_GetTicks();                       
                while (SDL_PollEvent(&e)) {
                        if (SDL_EVENT_QUIT == e.type) {
                                return;
                        } else if (SDL_EVENT_KEY_DOWN == e.type) {
                                input = TRUE;
                                press_time = curr_time;

                                if (SDLK_ESCAPE == e.key.key) {
                                        return;
                                } else if (!reg_keyb_input(e)) {
                                        return;
                                }

                                // Only update txt.typed_aft on cursor motion.
                        }
//                        else if (SDL_EVENT_MOUSE_BUTTON_DOWN == e.type) {
//                                SDL_MouseButtonEvent m = e.button;
//                                printf("%f %f\n", m.x, m.y);
//                                // Then... work on better text rendering first.
//                        }
                        /*      Go and see if it is hovering over text (may
                         *      want to first do better text rendering) and
                         *      then find where exactly the mouse is hovering
                         *      and thus move cursor... =o
                         *
                         */
                }

                        // 2 second break since last input then append.
                if (could_append && (curr_time - press_time) / 1000 >= 2) {
                        do_append();
                }

                if (!input) {
                        goto cont;
                }

                sprintf(txt.display, "%s%s|%s",
                        txt.typed_fore, txt.typing, txt.typed_aft);

                clear_cache();
                if (!font_rend_text(txt.display, 50, 50)) {
                        log_err("Error printing message.");
                        return;
                }

cont:
                clear_frame();
                rend_cache();
                draw_cursor();
                flush_frame();
                input = FALSE;
        }
}
