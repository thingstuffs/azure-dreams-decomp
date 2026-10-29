#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Run town service callback 0x238 with (0xE, 0x200). */
void call_scene_service_238_e_200(void) {
    town_scene_root->services->callback_238(0xE, 0x200);
}
