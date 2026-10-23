#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Initialize both linked record values to 0x4E0. */
void set_scene_record_base_offsets(void) {
    ((TownPositionState *)town_scene_root->position)->x = 0x4E0;
    ((TownPositionState *)town_scene_root->position)->y = 0x4E0;
}
