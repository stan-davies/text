#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

struct str create_str(
        void
) {
        char *base = calloc(1, sizeof(char));
        struct str s = {
                .beg    = base          ,
                .end    = base          ,
                .len    = 1
        };

        return s;
}

void dest_str(
        struct str             *s
) {
        if (NULL == s->beg) {
                return;
        }

        free(s->beg);
        s->beg = NULL;
}

int resize_str(
        struct str             *s       ,
        int                     r
) {
        if (s->len + r < 0) {           // Not allowed.
                return FALSE;
        }

        s->len += r;

        if (0 == s->len) {              // Emptied.
                if (s->beg != NULL) {
                        free(s->beg);
                        s->beg = s->end = NULL;
                }                       // But was already empty.

                return TRUE;
        }

        size_t end_offset;
        if (NULL == s->end) {
                end_offset = 0;
        } else {
                end_offset = s->end - s->beg;
        }
        s->beg = realloc(s->beg, s->len * sizeof(char));
        if (NULL == s->beg) {
                log_err("Failed to resize string.");
                return FALSE;
        }
        s->end = s->beg + end_offset;

        return TRUE;
}
