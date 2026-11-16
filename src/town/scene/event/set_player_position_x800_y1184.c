#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the scene position to x 800, y 1184. */
void set_player_position_x800_y1184(void) {
    town_scene_root->position->x = 800;
    town_scene_root->position->y = 1184;
}
