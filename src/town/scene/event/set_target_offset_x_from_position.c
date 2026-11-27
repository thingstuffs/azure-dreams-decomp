#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "shared/town_root.h"
/* Call the scene object's 0x248 method, then copy the state's two coordinate pairs across with an offset. */
void set_target_offset_x_from_position(void)
{
    TownPositionState *state;
    TownPositionState *state_2;
    town_scene_root->services->callback_248(0);
    state = town_scene_root->position;
    state->script_var_4 = state->x + 0x28;
    state_2 = town_scene_root->position;
    state_2->script_var_5 = state_2->y;
}
