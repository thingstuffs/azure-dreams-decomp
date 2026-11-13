#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Builds the land building in slot 2 with palette 0x12. */
void build_scene_land_building(void) {
    town_scene_root->services->BuildLandBuilding(2, 0x12);
}
