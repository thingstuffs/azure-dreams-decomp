#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/object.h"


/* Set the current object's inner values to 1696 and 1184. */
void set_player_position_x1696_y1184(void) {
    town_scene_root->position->x = 1696;
    town_scene_root->position->y = 1184;
}
