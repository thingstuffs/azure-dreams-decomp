#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 scene_charge;

/* Subtracts the global decrement from the current state's counter. */
void subtract_cached_value_from_money(void) {
    TownStateRecord *state;

    state = town_scene_root->town_state;
    state->money = (s32) (((signed int)state->money) - scene_charge);
}
