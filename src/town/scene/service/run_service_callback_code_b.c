#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x1E8 with code 2. */
void run_service_callback_0x1e8_with_code_2(void) {
    town_scene_root->services->callback_1E8(2);
}
