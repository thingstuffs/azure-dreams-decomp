#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x04C with (2, 0x12). */
void invoke_service_callback_04c_with_2_0x12(void) {
    town_scene_root->services->callback_04C(2, 0x12);
}
