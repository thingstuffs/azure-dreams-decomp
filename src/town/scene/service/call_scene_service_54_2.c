#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x054 with (2). */
void call_scene_service_54_2(void) {
    D_80016000->unk_20->callback_054(2);
}
