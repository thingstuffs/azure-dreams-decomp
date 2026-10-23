#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/town.h"
#include "slus.h"
#include "slus/data.h"

/* Finds or loads the three initial town object resources in order 0, 2, 1. */
void init_town_runtime_objects(void) {
    find_or_load_runtime_resource_key(&town_initial_object_resource_0);
    find_or_load_runtime_resource_key(&town_initial_object_resource_2);
    find_or_load_runtime_resource_key(&town_initial_object_resource_1);
}
