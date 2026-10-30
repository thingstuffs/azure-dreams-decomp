#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the town substate values to 800 and 1184. */
void set_scene_substate_offsets(void) {
    town_scene_root->position->x = 800;
    town_scene_root->position->y = 1184;
}
