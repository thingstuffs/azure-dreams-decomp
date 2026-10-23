#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 scene_progress_step;


/* Checks whether the stored value meets the D_8001C368 threshold. */
s32 is_progress_at_threshold(void) {
    return (u32) town_scene_root->town_state->money >= (u32) scene_progress_step;
}
