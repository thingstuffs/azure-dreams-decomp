#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns whether the referenced record's signed value at offset 0x35BE is at least 51. */
s32 is_state_counter_35be_at_least_51(void) {
    return town_scene_root->town_state->unk_35BE >= 0x33;
}
