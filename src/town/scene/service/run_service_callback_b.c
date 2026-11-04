#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Run town service callback 0x1E8 with (1). */
void run_service_callback_1(s32 unused_value, s32 unused_context) {
    town_scene_root->services->callback_1E8(1);
}
