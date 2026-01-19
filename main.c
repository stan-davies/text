#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text/text.h"

int main(void) {
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

        return 0;
}
