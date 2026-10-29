#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/money.h"



/* Returns whether the current record's value at offset 0x2D5C is at least 100. */
s32 has_money_at_least_100(void) {
    return (u32) town_scene_root->town_state->money >= 0x64U;
}
