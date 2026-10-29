#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/money.h"



/* Check whether the stored value meets the minimum. */
s32 has_money_at_least(u32 minimum) {
    return (u32) town_scene_root->town_state->money >= minimum;
}
