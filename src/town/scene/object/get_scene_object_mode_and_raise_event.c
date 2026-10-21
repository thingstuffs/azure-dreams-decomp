#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x84 with zero. */
void invoke_scene_callback(void) {
    D_80016000->unk_20->callback_084(0);
}
