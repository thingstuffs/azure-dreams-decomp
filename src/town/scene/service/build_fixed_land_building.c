#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x04C with (0x11, 0x10). */
void build_fixed_land_building(void) {
    town_scene_root->services->BuildLandBuilding(0x11, 0x10);
}
