#include "writer.h"

#include <stdlib.h>
#include <string.h>

#include "util.h"

// String stuff.
struct str {
        char           *str     ;       // Don't tamper with.
        size_t          len     ;       // Allocated size.
        char           *edt     ;       // Tamper with to heart's content.
        size_t          edt_len ;       // Size filled.
};

static struct str create_str(
        size_t          _len
) {
        struct str s;

        s.len = _len;
        s.str = calloc(s.len, sizeof(char));
        s.edt = s.str;
        s.edt_len = 0;

        return s;
}

static void free_str(
        struct str     *s
) {
        free(s->str);
        s->str = s->edt = NULL;
        s->len = s->edt_len = 0;
}

// Writer itself.

static struct {
        struct str      txt             ;
        struct str      curr_line       ;
        struct str      curr_word       ;
} writer;

void init_writer(
        char           *_txt            ,
        int             chars_per_line
) {
        writer.txt = create_str(strlen(_txt));
        strcpy(writer.txt.str, _txt);

        writer.curr_line = create_str(chars_per_line + 1);
        writer.curr_word = create_str(chars_per_line + 1);
}

void dest_writer(
        void
) {
        free_str(&writer.txt);
        free_str(&writer.curr_word);
        free_str(&writer.curr_line);
}

static void clear_word(
        void
) {
        writer.curr_word.edt = writer.curr_word.str;
        writer.curr_word.edt_len = 0;
}

static void clear_line(
        void
) {
        writer.curr_line.edt = writer.curr_line.str;
        writer.curr_line.edt_len = 0;
}

int writer_getline(
        char          **ln
) {
        int more_text = TRUE;
        int lbreak = FALSE;
        clear_line();
        for (;;) {
                clear_word();
                for (;;) {
                        if (' ' == *writer.txt.edt) {
                                break;
                        } else if ('\0' == *writer.txt.edt) {
                                lbreak = TRUE;
                                more_text = FALSE;
                                break;
                        } else if ('\n' == *writer.txt.edt) {
                                lbreak = TRUE;
                                break;
                        } else if (writer.curr_word.edt_len == writer.curr_word.len - 1) {
                                writer.txt.edt++;
                                goto flush;
                        }
                        *writer.curr_word.edt++ = *writer.txt.edt++;
                        writer.curr_word.edt_len++;
                }

                writer.txt.edt++;       // Move past control character.

                if (writer.curr_line.edt_len + writer.curr_word.edt_len > writer.curr_line.len) {
                        writer.txt.edt_len -= writer.curr_word.edt_len;
flush:
                        *--writer.curr_line.edt = '\0'; // Replace end ' '.
                        strcpy(*ln, writer.curr_line.str);
                        return more_text;
                }

                *writer.curr_word.edt++ = ' ';
                *writer.curr_word.edt = '\0';
                strcpy(writer.curr_line.edt, writer.curr_word.str);
                writer.curr_line.edt += writer.curr_word.edt_len + 1;
                writer.curr_line.edt_len += writer.curr_word.edt_len + 1;

                if (lbreak) {
                        goto flush;
                }
        }
}
