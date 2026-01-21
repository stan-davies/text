#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#include "sdl-util/sdl-util.h"

#include "rend/rend.h"
#include "text/text.h"
#include "cycl/cycl.h"

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

        cycle();

        dest_txt_man();
        dest_rend();
        end_sdl(&win);

        return 0;
}
