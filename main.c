#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#include "sdl-util/sdl-util.h"

#include "rend/rend.h"
#include "text/text.h"
#include "cycl/cycl.h"
#include "keys/keys.h"

int main(int argc, char **argv) {
        init_logw();

        log_msg("Initialising...");

        SDL_Window *win;

        if (!init_sdl(&win)) {
                return 0;
        }

        if (!init_rend(win)) {
                // What to do?
        }
        init_txt_man();
        init_keys();

        log_msg("Program started successfully.\n-----");

        txt_append("world");
        txt_move_cursor(-5);
        txt_append("hello ");
        txt_move_cursor(5);
        txt_append("!");
        txt_move_cursor(-6);

        init_cycle();
        cycle();
        end_cycle();

        log_msg("-----\nProgram quit, ending...");

        dest_keys();
        dest_txt_man();
        dest_rend();
        end_sdl(&win);

        log_msg("Program ended successfully.");

        return 0;
}
