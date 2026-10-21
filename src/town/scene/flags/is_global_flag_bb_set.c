#include "common.h"

extern s32 scene_update_state;

/* Returns whether D_80019BB0 is nonzero. */
s32 is_global_flag_19_bb_0_set(void) {
    return scene_update_state != 0;
}
