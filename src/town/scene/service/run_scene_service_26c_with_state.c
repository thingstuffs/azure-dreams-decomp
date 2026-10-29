#include "modules/town_ovl_3fe0d0_p00.h"
#include "town/scene/service.h"

s32 run_scene_service_26c_with_state(void) {
    return town_scene_root->services->callback_26C(&scene_event_data,
        (u8 *)town_scene_root->town_state + 0x20C);
}
