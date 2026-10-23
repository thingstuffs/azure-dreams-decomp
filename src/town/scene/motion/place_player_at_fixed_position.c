#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/fixed_position.h"

void set_player_fixed_position(void) {
    ((TownPositionState *)town_scene_root->position)->x = 864;
    ((TownPositionState *)town_scene_root->position)->y = 1056;
}
