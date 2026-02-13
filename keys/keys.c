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

void init_keys(
        void
) {
        keys.sq = calloc(MAX_KEY_SQ_LN, sizeof(char));

        log_msg("  Initialised key manager.");
}

void dest_keys(
        void
) {
        free(keys.sq);
        keys.sq = NULL;
        keys.sq_l = 0;

        log_msg("  Ended key manager.");
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

        if (k >= SDL_SCANCODE_CAPSLOCK) {       // All non-printable here and beyond.
                ret = KEYP_NOTHING;
                goto exit;
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
        case SDL_SCANCODE_BACKSPACE:
                if (keys.sq_l > 0) {
                        keys.sq_l--;
                        ret = KEYP_INPUT;
                } else {
                        ret = KEYP_BACKSPACE;
                }
                break;
        case SDL_SCANCODE_TAB:
                ret = KEYP_NOTHING;
                break;
        default:
                keys.sq[keys.sq_l++] = SDL_GetKeyFromScancode(k, SDL_KMOD_SHIFT * shift_d, false);
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

int sprint_keybuf(
        char                  **s
) {
        char *c = keys.sq;
        char *e = *s;

        while (c < keys.sq + keys.sq_l) {
                *e++ = *c++;
        }
        *e = '\0';

        return keys.sq_l;
}

int flush_keybuf(
        void
) {
        keys.sq[keys.sq_l] = '\0';      // = 0
        if (!txt_append(keys.sq)) {
                log_err("Failed to append input.");
                return FALSE;
        }
        keys.sq_l = keys.sq[0] = 0;     // = '\0'
        return TRUE;
}

