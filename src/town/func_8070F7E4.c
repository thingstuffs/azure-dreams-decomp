#include "common.h"
#include "town/scene/record_services.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_8001B0D8[];

/* Run town service callback 0X218 with this module's record D_8001B0D8 (this TOWN module's copy of the town/func_8032D78C wrapper). */
void run_scene_record_service_c(void) {
    town_scene_root->services->callback_218(D_8001B0D8);
}
