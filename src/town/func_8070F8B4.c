#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x280 with the code plus flag 0x1000. */
void dispatch_flagged_command(s32 code) {
    D_80016000->unk_20->callback_280(code | 0x1000);
}
