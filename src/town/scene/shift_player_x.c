#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
/* Call the scene object's 0x248 method, then advance the state's x field by 0x20. */
void shift_player_x(void)
{
    TownPositionState *state;
    town_scene_root->services->callback_248(0);
    state = town_scene_root->position;
    state->x = state->x + 0x20;
}
