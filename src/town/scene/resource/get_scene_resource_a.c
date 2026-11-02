#include "common.h"
#include "m2c_compat.h"
#include "town/scene/resource.h"
#include "town/scene/flags.h"
extern M2C_UNK D_8001CC5C;

/* Call func_80017BA0, then return the address of D_8001CC5C. */
s32 *get_scene_resource_a(s32 first_input, s32 second_input) {
    set_indexed_entry_flag(first_input, second_input);
    return &D_8001CC5C;
}
