#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/town.h"
#include "slus.h"
#include "slus/data.h"

/* Applies func_8003C758 to the three global runtime objects. */
void init_town_runtime_objects(void) {
    find_or_load_runtime_resource_key(&town_initial_object_resource_0);
    find_or_load_runtime_resource_key(&town_initial_object_resource_2);
    find_or_load_runtime_resource_key(&town_initial_object_resource_1);
}
