#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 Callback(s32);


/* Calls the callback with zero, then maps states 0, 1, and 2 to output values 1, 2, and 3. */
void remap_player_state(void)
{
    TownPositionState *state_check_one;
    TownPositionState *state_check_zero;
    TownPositionState *state_check_two;

    town_scene_root->services->callback_244(0);
    town_scene_root->position->script_var_14 = 0;
    state_check_zero = town_scene_root->position;
    if (state_check_zero->script_var_0 == 0) {
        state_check_zero->script_var_14 = 1;
    }
    state_check_two = town_scene_root->position;
    if (state_check_two->script_var_0 == 2) {
        state_check_two->script_var_14 = 3;
    }
    state_check_one = town_scene_root->position;
    if (state_check_one->script_var_0 == 1) {
        state_check_one->script_var_14 = 2;
    }
}
