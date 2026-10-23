#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns whether the stored value is below the threshold. */
s32 is_money_below(u32 threshold) {
    return (u32) town_scene_root->town_state->money < threshold;
}
