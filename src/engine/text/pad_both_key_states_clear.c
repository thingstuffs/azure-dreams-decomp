#include "slus.h"
#include "common.h"
#include "engine/text.h"

/* Returns 1 when pad key states 1 and 4 are both zero. */
s32 pad_both_key_states_clear(void) {
    s32 keys_clear = 0;

    if (read_sound_mode_blocking_status(1) == 0) {
        if (read_sound_mode_blocking_status(4) == 0) {
            keys_clear = 1;
        }
    }
    return keys_clear;
}
