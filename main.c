#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#include "sdl-util/sdl-util.h"

#include "rend/rend.h"
#include "text/text.h"

int main(int argc, char **argv) {
        SDL_Window *win;

        if (!init_sdl(&win)) {
                return 0;
        }

        init_rend(win);

        init_text_man();

        append_txt("world");
        print_txt();

        move_cursor(-5);
        print_txt();
        
        append_txt("hello ");
        print_txt();

        move_cursor(11);
        print_txt();

        append_txt("!");
        print_txt();

        dest_text_man();

        SDL_Event e;
        int run = TRUE;
        while (run) {
                rendcl();

                while (SDL_PollEvent(&e)) {
                        if (SDL_EVENT_QUIT == e.type) {
                                run = FALSE;
                        } else if (SDL_EVENT_KEY_DOWN == e.type) {
                                if (SDLK_X == e.key.key) {
                                        run = FALSE;
                                }
                        }
                }

                push_rend();
        }

        dest_rend();
        end_sdl(&win);

        return 0;
}
