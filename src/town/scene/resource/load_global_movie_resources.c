#include "common.h"
#include "engine/scene.h"
#include "town/scene/resource.h"

extern u32 town_scene_resource_descriptor[2];
extern u32 D_800D1D54[2];

/* Process both global objects with file_load_com, then call reserve_twch_load with 3. */
void load_global_movie_resources(void) {
    file_load_com(&town_scene_resource_descriptor);
    file_load_com(D_800D1D54);
    reserve_twch_load(3);
}
