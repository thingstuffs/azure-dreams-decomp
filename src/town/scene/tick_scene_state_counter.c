#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"



extern s32 D_80019438;

/* Decrements the current state's counter by D_80019438. */
void tick_scene_state_counter(void) {
    TownStateRecord *counter_state;

    counter_state = town_scene_root->town_state;
    counter_state->money = (s32) (((signed int)counter_state->money) - D_80019438);
}
