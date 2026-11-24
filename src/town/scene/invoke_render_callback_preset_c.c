#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

/* Invoke the callback at offset 0x278 with settings (10, 1, 0, 15). */
void invoke_render_callback_preset_c(void) {
    town_scene_root->services->callback_278(10, 1, 0, 15);
}
