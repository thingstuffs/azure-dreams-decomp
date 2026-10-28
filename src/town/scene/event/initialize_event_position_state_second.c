#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef s32 (*Callback)(s32);


/* Run two callbacks and initialize offset and saved coordinates from the current position. */
void initialize_event_position_state(void) {
    TownPositionState *offset_x_state;
    TownPositionState *offset_y_state;
    TownPositionState *saved_x_state;
    TownPositionState *saved_y_state;

    ((Callback)town_scene_root->services->callback_248)(0);
    offset_x_state = town_scene_root->position;
    offset_x_state->unk_10 = offset_x_state->x + 0x20;
    offset_y_state = town_scene_root->position;
    offset_y_state->unk_14 = offset_y_state->y;
    ((Callback)town_scene_root->services->callback_258)(0xD);
    saved_x_state = town_scene_root->position;
    saved_x_state->unk_18 = saved_x_state->x;
    saved_y_state = town_scene_root->position;
    saved_y_state->unk_1C = saved_y_state->y;
}
