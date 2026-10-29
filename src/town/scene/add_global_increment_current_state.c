#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"



extern s32 scene_price;

/* Adds the global increment to the current state's accumulator. */
void add_global_increment_current_state(void) {
    TownStateRecord *state;

    state = town_scene_root->town_state;
    state->money = (s32) (((signed int)state->money) + scene_price);
}
