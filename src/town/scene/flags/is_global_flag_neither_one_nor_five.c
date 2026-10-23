#include "common.h"

extern s32 scene_update_state;

/* Returns whether scene_update_state is neither 1 nor 5. */
s32 is_global_flag_neither_one_nor_five(void) {
    s32 is_other;

    is_other = 0;
    if (scene_update_state != 1) {
        is_other = scene_update_state != 5;
    }
    return is_other;
}
