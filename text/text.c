#include "text.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "str/str.h"

/*
 *      A text block. Has an ID as well as dedicated right/left sides around a
 *      split, i.e. wherever is being edited.
 */
static struct {
        struct str      fore    ;       // Left text (edit at head of).
        struct str      aft     ;       // Right text (in reverse).
} txt;


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
        c = txt.aft.end;
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

        if (0 == offset) {
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
