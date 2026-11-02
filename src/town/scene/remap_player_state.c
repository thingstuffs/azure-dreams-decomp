#include "shared/record_ptrs.h"
#include "shared/town_root.h"
typedef signed char s8;
typedef int s32;

typedef s32 Callback(s32);


/* Calls the callback with zero, then maps states 0, 1, and 2 to output values 1, 2, and 3. */
void remap_player_state(void)
{
    TownPositionState *state_check_one;
    TownPositionState *state_check_zero;
    TownPositionState *state_check_two;

    town_scene_root->services->callback_244(0);
    town_scene_root->position->unk_38 = 0;
    state_check_zero = town_scene_root->position;
    if (state_check_zero->unk_00 == 0) {
        state_check_zero->unk_38 = 1;
    }
    state_check_two = town_scene_root->position;
    if (state_check_two->unk_00 == 2) {
        state_check_two->unk_38 = 3;
    }
    state_check_one = town_scene_root->position;
    if (state_check_one->unk_00 == 1) {
        state_check_one->unk_38 = 2;
    }
}
