#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x84 with zero. */
void invoke_scene_callback(void) {
    town_scene_root->services->callback_084(0);
}
