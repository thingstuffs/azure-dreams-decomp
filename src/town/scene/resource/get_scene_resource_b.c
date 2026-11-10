#include "common.h"
#include "town/scene/resource.h"
#include "town/scene/flags.h"

extern s32 D_80019184[];

/* Call func_80017BA0, then return D_80019184. */
s32 *get_scene_resource_b(s32 first_input, s32 second_input) {
    set_indexed_entry_flag(first_input, second_input);
    return D_80019184;
}
