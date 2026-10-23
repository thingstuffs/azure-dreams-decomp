#include "modules/town_ovl_3fe0d0_p00.h"

void run_scene_service_26c_with_state(void) {
    ((s32 (*) (s32 *, s32))town_scene_root->services->callback_26C)(&scene_event_data,
        ((s32)town_scene_root->town_state) + 0x20C);
}
