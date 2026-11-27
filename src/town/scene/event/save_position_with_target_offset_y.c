#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/event.h"


/* Invoke state callbacks and copy the base position into two pairs, offsetting the first Y by 32. */
void save_position_with_target_offset_y(void) {
    TownPositionState *first_x_state;
    TownPositionState *first_y_state;
    TownPositionState *second_x_state;
    TownPositionState *second_y_state;

    ((s32 (*) (s32))town_scene_root->services->callback_248)(0);
    first_x_state = town_scene_root->position;
    first_x_state->script_var_4 = (s32) first_x_state->x;
    first_y_state = town_scene_root->position;
    first_y_state->script_var_5 = (s32) (first_y_state->y + 0x20);
    ((s32 (*) (s32))town_scene_root->services->callback_258)(0xD);
    second_x_state = town_scene_root->position;
    second_x_state->script_var_6 = (s32) second_x_state->x;
    second_y_state = town_scene_root->position;
    second_y_state->script_var_7 = (s32) second_y_state->y;
}
