#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x238 with (0xF, 0x201). */
void call_scene_service_238_f_201(void) {
    D_80016000->unk_20->callback_238(0xF, 0x201);
}
