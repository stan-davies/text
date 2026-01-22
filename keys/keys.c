#include "keys.h"

#include <stdio.h>
#include <stdlib.h>

#include "text/text.h"

#define MAX_KEY_SQ_LN           128

static struct {
        char                   *sq      ;       // Sequence.
        int                     sq_l    ;       // Sequence length.
} keys = {
        .sq             =       NULL    ,
        .sq_l           =       0
};

static void clear_keybuf(
        void
) {
        keys.sq_l = keys.sq[0] = 0;
}

void init_keys(
        void
) {
        keys.sq = calloc(MAX_KEY_SQ_LN, sizeof(char));
}

void dest_keys(
        void
) {
        free(keys.sq);
        keys.sq = NULL;
        keys.sq_l = 0;
}

int log_keyp(
        SDL_Keycode             k
) {
        if (keys.sq_l >= MAX_KEY_SQ_LN) {
                return KEYP_ERROR;
        }

        if (SDLK_RETURN == k) {
                keys.sq[keys.sq_l] = '\0';
                if (!append_txt(keys.sq)) {
                        log_err("Failed to append input.");
                        return KEYP_ERROR;
                }
                clear_keybuf();
                return KEYP_APPEND;
        }

        keys.sq[keys.sq_l++] = k;       // Need to validate characters somehow.
        return KEYP_INPUT;
}

int get_maxkeys(
        void
) {
        return MAX_KEY_SQ_LN;
}

void sprint_keybuf(
        char                  **s
) {
        char *c = keys.sq;
        char *e = *s;

        while (c < keys.sq + keys.sq_l) {
                *e++ = *c++;
        }
        *e = '\0';
}
