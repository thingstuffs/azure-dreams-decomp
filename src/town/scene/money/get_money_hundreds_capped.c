#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/money.h"


/* Adds 100 to the stored value, divides by 100, and caps the result at ten. */
s32 get_money_hundreds_capped(void) {
    u32 value;

    value = (town_scene_root->town_state->money + 0x64U) / 100U;
    if ((s32)value >= 0xB) {
        value = 0xAU;
    }
    return value;
}
