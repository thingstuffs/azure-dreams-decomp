#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/object.h"


/* Set the referenced object's unk4 and unk8 fields to 800 and 736. */
void set_player_position_x800_y736(void) {
    town_scene_root->position->x = 800;
    town_scene_root->position->y = 736;
}
