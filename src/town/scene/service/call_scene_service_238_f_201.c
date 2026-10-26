#include "common.h"
#include "town/scene/service.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x238 with (0xF, 0x201). */
s32 call_scene_service_238_f_201(void) {
    return town_scene_root->services->callback_238(0xF, 0x201);
}
