#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x04C with (0x11, 0x10). */
void run_service_callback_0x78(void) {
    D_80016000->unk_20->callback_04C(0x11, 0x10);
}
