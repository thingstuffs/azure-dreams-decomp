#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0X78 with zero (this TOWN module's copy of the town/func_8035A5E4 wrapper). */
void run_service_callback_0x78(void) {
    town_scene_root->services->callback_078(0);
}
