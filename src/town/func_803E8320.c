#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Invoke the scene service at offset 0x280 with request 0x1704. */
void invoke_scene_service(void) {
    D_80016000->unk_20->callback_280(0x1704);
}
