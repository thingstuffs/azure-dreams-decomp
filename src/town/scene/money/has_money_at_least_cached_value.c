#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 scene_charge;


/* Check whether the stored value meets the D_80019B00 threshold. */
s32 has_money_at_least_cached_value(void) {
    return (u32) town_scene_root->town_state->money >= (u32) scene_charge;
}
