#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Initialize both linked record values to 0x4E0. */
void set_library_exit_target(void) {
    town_scene_root->position->x = 0x4E0;
    town_scene_root->position->y = 0x4E0;
}
