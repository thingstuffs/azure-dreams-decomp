#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Invoke the callback at offset 0x1E8 with code 7. */
void invoke_callback_code_7(void) {
    town_scene_root->services->callback_1E8(7);
}
