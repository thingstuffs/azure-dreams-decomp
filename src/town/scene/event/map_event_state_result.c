#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "shared/town_root.h"

typedef s32 Callback(s32);


/* Calls the callback with zero, then maps states 0-2 to results 1-3, defaulting to zero. */
void map_event_state_result(void)
{
    TownPositionState *state_one;
    TownPositionState *state_two;
    TownPositionState *state_zero;

    town_scene_root->services->callback_244(0);
    town_scene_root->position->script_var_14 = 0;
    state_zero = town_scene_root->position;
    if (state_zero->script_var_0 == 0) {
        state_zero->script_var_14 = 1;
    }
    state_one = town_scene_root->position;
    if (state_one->script_var_0 == 1) {
        state_one->script_var_14 = 2;
    }
    state_two = town_scene_root->position;
    if (state_two->script_var_0 == 2) {
        state_two->script_var_14 = 3;
    }
}
