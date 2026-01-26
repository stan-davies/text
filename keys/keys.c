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

static int flush_keybuf(
        void
) {
        keys.sq[keys.sq_l] = '\0';      // = 0
        if (!append_txt(keys.sq)) {
                log_err("Failed to append input.");
                return FALSE;
        }
        keys.sq_l = keys.sq[0] = 0;     // = '\0'
        return TRUE;
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
        SDL_Scancode            k       ,
        int                     shift_d
) {
        int ret = KEYP_INPUT;
        if (keys.sq_l >= MAX_KEY_SQ_LN) {
                if (!flush_keybuf()) {
                        ret = KEYP_ERROR;
                        goto exit;
                }

                ret = KEYP_APPEND;      // Don't exit yet though - ensure update.
        }

        switch (k) {
        case SDL_SCANCODE_RETURN: 
                keys.sq[keys.sq_l++] = '\n';
                // Perhaps not necessary but seems sensible enough.
                ret = flush_keybuf() ? KEYP_APPEND : KEYP_ERROR;
                break;
        case SDL_SCANCODE_LSHIFT:
                ret = KEYP_NOTHING;
                break;
        default:
                keys.sq[keys.sq_l++] = SDL_GetKeyFromScancode(k, SDL_KMOD_SHIFT * shift_d, false);
                        // Need to validate characters somehow. Add some kind
                        // of 'keycode_to_charcode(code, shift_down)'
                break;
        }

exit:
        return ret;
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
