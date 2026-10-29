#include "common.h"
#include "town/scene/resource.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019184[];
void func_80017BA0(s32, s32);                            /* extern */

/* Call func_80017BA0, then return D_80019184. */
s32 *get_scene_resource_b(s32 first_input, s32 second_input) {
    func_80017BA0(first_input, second_input);
    return D_80019184;
}
