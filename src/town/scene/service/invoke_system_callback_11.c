#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void invoke_system_callback_11(void) {
    town_scene_root->services->callback_238(0x11, 0x200);
}
