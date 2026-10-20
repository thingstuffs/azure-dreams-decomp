#include "common.h"
#include "m2c_compat.h"
void func_80017BA0(s32, s32);                            /* extern */
extern M2C_UNK D_8001CC5C;

/* Call func_80017BA0, then return the address of D_8001CC5C. */
s32 *get_scene_resource_a(s32 first_input, s32 second_input) {
    func_80017BA0(first_input, second_input);
    return &D_8001CC5C;
}
