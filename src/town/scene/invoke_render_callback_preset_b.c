#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


/* Invoke the callback at offset 0x278 with settings (1, 1, 0, 0x1E). */
void invoke_render_callback_preset_b(void) {
    town_scene_root->services->callback_278(1, 1, 0, 0x1E);
}
