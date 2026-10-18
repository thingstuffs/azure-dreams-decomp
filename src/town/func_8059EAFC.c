#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x1E8 with (8). */
void run_service_callback_8(void) {
    D_80016000->unk_20->callback_1E8(8);
}
