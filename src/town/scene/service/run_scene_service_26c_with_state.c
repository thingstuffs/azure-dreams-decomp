#include "modules/town_ovl_3fe0d0_p00.h"

void run_scene_service_26c_with_state(void) {
    ((s32 (*) (s32 *, s32))D_80016000->unk_20->callback_26C)(&scene_event_data,
        ((s32)D_80016000->unk_38) + 0x20C);
}
