#include "common.h"

typedef s32 T;

extern T file_load_com();
extern T reserve_twch_load();
extern T town_scene_resource_descriptor;
extern T D_800D1D54;

/* Process both global objects with file_load_com, then call reserve_twch_load with 3. */
void load_global_movie_resources(void) {
    file_load_com(&town_scene_resource_descriptor);
    file_load_com(&D_800D1D54);
    reserve_twch_load(3);
}
