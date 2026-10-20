#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x280 with (0xB1). */
void call_scene_service_280_b1(void) {
    D_80016000->unk_20->callback_280(0xB1);
}
