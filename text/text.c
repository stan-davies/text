#include "text.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

/**     Structure definitions.                                         **/

/*
 *      Basic, safer string with start and end pointers and a length.
 */
struct str {
        char           *beg     ;       // Data begin.
        char           *end     ;       // Data end - on the null terminator.
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
        char *base = calloc(1, sizeof(char));
        struct str s = {
                .beg    = base  ,
                .end    = base  ,
                .len    = 1
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

static int resize_str(
        struct str             *s       ,
        int                     r
) {
        if (s->len + r < 0) {           // Not allowed.
                return -1;
        }

        s->len += r;

        if (0 == s->len) {              // Emptied.
                if (s->beg != NULL) {
                        free(s->beg);
                        s->beg = s->end = NULL;
                }                       // But was already empty.

                return 0;
        }

        size_t end_offset;
        if (NULL == s->end) {
                end_offset = 0;
        } else {
                end_offset = s->end - s->beg;
        }
        s->beg = realloc(s->beg, s->len * sizeof(char));
        s->end = s->beg + end_offset;

        return s->len;
}

/**     Function definitions                                            **/

void init_txt_man(
        void
) {
        txt.fore = create_str();
        txt.aft  = create_str();
}

void dest_txt_man(
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
        printf("|");
        c = txt.aft.end + txt.aft.len;
        while (c > txt.aft.beg) {
                printf("%c", *--c);
        }
        printf("'\n");
}

#define TXT_FORE_MASK   TXT_FORE
#define TXT_AFT_MASK    TXT_AFT

void sprint_txt(
        char                  **s       ,
        int                     bits
) {
        int len = 1 +                   // +1 for '\0'
                  txt.fore.len * (TXT_FORE == (bits & TXT_FORE_MASK)) +
                  txt.aft.len  * (TXT_AFT  == (bits & TXT_AFT_MASK ));
        *s = realloc(*s, len * sizeof(char));
        char *e = *s;
        char *c;
        if (TXT_FORE == (bits & TXT_FORE_MASK)) {
                c = txt.fore.beg;
                while (c < txt.fore.end) {
                        *e++ = *c++;                
                }
        }
        if (TXT_AFT == (bits & TXT_AFT_MASK)) {
                c = txt.aft.end;
                while (c > txt.aft.beg) {
                        *e++ = *--c;
                }
        }
        *e = '\0';
}

int append_txt(
        char                   *s
) {
        if (resize_str(&txt.fore, strlen(s)) <= 0) {
                return FALSE;
        }

        char *c = s;
                                // End has been moved after realloc.
        char *new_e = txt.fore.end + strlen(s);
        while (txt.fore.end < new_e) {
                *txt.fore.end++ = *c++;
        }
        *txt.fore.end = '\0';

        return TRUE;
}

int move_cursor(
        int                     offset          // Needs to be signed.
) {
        struct str *src = NULL;
        struct str *dst = NULL;

        if (offset < 0) {
                src = &txt.fore;
                dst = &txt.aft;
        } else if (offset > 0) {
                src = &txt.aft;
                dst = &txt.fore;
        }

        offset = MIN(abs(offset), src->len - 1);    // -1 for null-terminator.

        if (0 == offset) {                 // Needed?
                return TRUE;
        }

        resize_str(dst, offset);
        char *new_e = src->end - offset;
        while (src->end > new_e) {
                *dst->end++ = *--src->end;
        }
        *src->end = '\0';
        resize_str(src, -offset);

        return TRUE;
}
