#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 town_stored_amount;

/* Add D_80018AE0 to the current state's accumulator. */
void apply_stored_amount_to_town(void) {
    TownStateRecord *state;

    state = town_scene_root->town_state;
    state->money = (s32) (((signed int)state->money) + town_stored_amount);
}
