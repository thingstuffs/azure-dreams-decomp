#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_80018864[];

/* Run town service callback 0x218 with this module's record D_80018864. */
void run_service_callback_module_record(void) {
    town_scene_root->services->callback_218(D_80018864);
}
