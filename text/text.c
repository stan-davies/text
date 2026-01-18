#include "text.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**     Structure definitions.                                         **/

/*
 *      Basic, safer string with start and end pointers and a length.
 */
struct str {
        char           *beg     ;       // Data begin.
        char           *end     ;       // Data end.
        size_t          len     ;       // Length of data.
};

/*
 *      A text block. Has an ID as well as dedicated right/left sides around a
 *      split, i.e. wherever is being edited.
 */
static struct {
        struct str      fore    ;       // Left text (edit at head of).
        struct str      aft     ;       // Right text (in reverse).
} txt;


/**     Private function declerations                                   **/

static struct str create_str(
        void
) {
        struct str s = {
                .beg    = NULL  ,
                .end    = NULL  ,
                .len    = 0
        };

        return s;
}

static void dest_str(
        struct str             *s
) {
        if (NULL == s->beg) {
                return;
        }

        free(s->beg);
        s->beg = NULL;
}

static void resize_str(
        struct str             *s       ,
        int                     r
) {
        if (s->len + r < 0) {           // IMPOSSIBLE
                return;
        }

        s->len += r;

        if (0 == s->len) {              // EMPTIED
                if (s->beg != NULL) {
                        free(s->beg);
                        s->beg = s->end = NULL;
                }                       // BUT WAS ALREADY EMPTY

                return;
        }

        s->beg = realloc(s->beg, s->len * sizeof(char));
        s->end = s->beg + s->len * sizeof(char);
}

/**     Function definitions                                            **/

void init_text_man(
        void
) {
        txt.fore = create_str();
        txt.aft  = create_str();

        resize_str(&txt.fore, 6);
        strcpy(txt.fore.beg, "hello");

        resize_str(&txt.aft, 6);
        strcpy(txt.aft.beg, "world");
}

void dest_text_man(
        void
) {
        dest_str(&txt.fore);
        dest_str(&txt.aft);
}

void print_txt(
        void
) {
        printf("'");
        char *c = txt.fore.beg;
        while (c < txt.fore.end) {
                printf("%c", *c++);
        }
        c = txt.aft.end + txt.aft.len;
        while (c > txt.aft.beg) {
                printf("%c", *--c);
        }
        printf("'\n");
}
