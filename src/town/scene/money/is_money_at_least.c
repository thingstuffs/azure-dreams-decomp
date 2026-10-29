#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/money.h"

/* Return whether the stored value has reached 10000. */
s32 is_money_at_least_10000(void) {
    return (u32) town_scene_root->town_state->unk_2D68 >= 0x2710U;
}
