#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/object.h"


/* Set the current inner object's unk4 and unk8 values to 1696 and 864. */
void set_player_position_x1696_y864(void) {
    town_scene_root->position->x = 1696;
    town_scene_root->position->y = 864;
}
