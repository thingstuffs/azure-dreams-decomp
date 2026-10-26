#include "common.h"
#include "town/scene/service.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x054 with (2). */
s32 call_scene_service_54_2(void) {
    return town_scene_root->services->callback_054(2);
}
