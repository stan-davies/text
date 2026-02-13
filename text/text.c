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
                .beg    = base          ,
//                .end    = base + 1      ,
                .end    = base          ,
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

/*
 * Alters the length of the given string, altering each datum accordingly -
 * note that the end pointer is placed at the same offset from the start, but
 * in the new memory block.
 * Returns success.
 */
static int resize_str(
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

/**     Function definitions                                            **/

void init_txt_man(
        void
) {
        txt.fore = create_str();
        txt.aft  = create_str();

        log_msg("  Initialised text manager.");
}

void dest_txt_man(
        void
) {
        dest_str(&txt.fore);
        dest_str(&txt.aft);

        log_msg("  Ended text manager.");
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
        *s = realloc(*s, len * sizeof(char));   // Freed by caller.
        if (NULL == *s) {
                log_err("realloc to null in `sprint_txt`");
        }
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

int get_txtlen(
        void
) {
        return txt.fore.len + txt.aft.len - 2;  // Account for each '\0'.
}

int txt_append(
        char                   *s
) {
        if (!resize_str(&txt.fore, strlen(s))) {
                return FALSE;
        }

        char *c = s;
                // End has also been moved after realloc, but distance from
                // beginning is preserved.
        char *new_e = txt.fore.end + strlen(s);
        while (txt.fore.end < new_e) {
                *txt.fore.end++ = *c++;
        }
        *txt.fore.end = '\0';

        return TRUE;
}

int txt_pop(
        void
) {
                // Don't want to shorten if string is "\0".
        if (1 == txt.fore.len) {
                log_msg("already empty");
                return TRUE;
        }

        if (!resize_str(&txt.fore, -1)) {
                return FALSE;
        }
        
        *--txt.fore.end = '\0';

        return TRUE;
}

int txt_move_cursor(
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

        if (!resize_str(dst, offset)) {
                return FALSE;
        }
        char *new_e = src->end - offset;
        while (src->end > new_e) {
                *dst->end++ = *--src->end;
        }
        *src->end = '\0';
        if (!resize_str(src, -offset)) {
                return FALSE;
        }

        return TRUE;
}
