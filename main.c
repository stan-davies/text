#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#include "sdl-util/sdl-util.h"

#include "rend/rend.h"
#include "text/text.h"
#include "font/font.h"

int main(int argc, char **argv) {
        SDL_Window *win;

        if (!init_sdl(&win)) {
                return 0;
        }

        init_rend(win);

        init_txt_man();

        append_txt("world");
        move_cursor(-5);
        append_txt("hello ");
        move_cursor(11);
        append_txt("!");

        char *txt;
        sprint_txt(&txt);

        SDL_Event e;
        int run = TRUE;
        while (run) {
                while (SDL_PollEvent(&e)) {
                        if (SDL_EVENT_QUIT == e.type) {
                                run = FALSE;
                        } else if (SDL_EVENT_KEY_DOWN == e.type) {
                                if (SDLK_X == e.key.key) {
                                        run = FALSE;
                                }
                        }
                }

                rendcl();
                if (!font_rend_text(txt, 50, 50)) {
                        printf("Error printing message.\n");
                        run = FALSE;
                }
                push_rend();
        }

        free(txt);
        txt = NULL;

        dest_txt_man();
        dest_rend();
        end_sdl(&win);

        return 0;
}
