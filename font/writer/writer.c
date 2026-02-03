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
                        log_msg("dealing with %d", *writer.txt.edt);
                        if (writer.txt.edt - writer.txt.str > writer.txt.len) {
                                log_err("gone beyond");
                        }
                        if (' ' == *writer.txt.edt) {
                                log_msg("break space");
                                break;
                        } else if ('\0' == *writer.txt.edt) {
                                lbreak = TRUE;
                                more_text = FALSE;
                                log_msg("break null");
                                break;
                        } else if ('\n' == *writer.txt.edt) {
                                lbreak = TRUE;
                                log_msg("break linefeed");
                                break;
                        } else if (writer.curr_word.edt_len == writer.curr_word.len - 1) {
                                writer.txt.edt++;
                                log_msg("break capacity");
                                goto flush;
                        }
                        *writer.curr_word.edt++ = *writer.txt.edt++;
                        writer.curr_word.edt_len++;
                }

                writer.txt.edt++;       // Move past control character.

                        // If word doesn't fit on line.
                if (writer.curr_line.edt_len + writer.curr_word.edt_len > writer.curr_line.len) {
                        writer.txt.edt_len -= writer.curr_word.edt_len;
flush:
                        *--writer.curr_line.edt = '\0'; // Replaces end ' '.
                        strcpy(*ln, writer.curr_line.str);
                        return more_text;
                }

                *writer.curr_word.edt++ = ' ';
                *writer.curr_word.edt = '\0';
                strcpy(writer.curr_line.edt, writer.curr_word.str);
                writer.curr_line.edt += writer.curr_word.edt_len + 1;
                writer.curr_line.edt_len -= writer.curr_word.edt_len + 1;
                // This occasionally fails to print?
                log_msg("adding word '%s' - total %d", writer.curr_word.str, writer.curr_word.edt_len);

                if (lbreak) {
                        goto flush;
                }
        }
}
