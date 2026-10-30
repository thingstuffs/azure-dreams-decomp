#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"


/* Set the current record's two state values to 0x560 and 0x3E0. */
void set_scene_record_state_offsets(void) {
    town_scene_root->position->x = 0x560;
    town_scene_root->position->y = 0x3E0;
}
