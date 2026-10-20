#include "common.h"
#include "m2c_compat.h"

#include "common.h"
s32 find_or_load_runtime_resource_key(s32 key);                   /* extern */
extern M2C_UNK town_initial_object_resource_0;
extern M2C_UNK town_initial_object_resource_1;
extern M2C_UNK town_initial_object_resource_2;

/* Applies func_8003C758 to the three global runtime objects. */
void init_town_runtime_objects(void) {
    find_or_load_runtime_resource_key(&town_initial_object_resource_0);
    find_or_load_runtime_resource_key(&town_initial_object_resource_2);
    find_or_load_runtime_resource_key(&town_initial_object_resource_1);
}
