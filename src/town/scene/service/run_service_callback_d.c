#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x04C with (0x11, 0x10). */
void run_service_callback_0x78(void) {
    town_scene_root->services->callback_04C(0x11, 0x10);
}
