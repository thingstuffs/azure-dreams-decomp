#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0X84 with zero (this TOWN module's copy of the town/func_8035A5E4 wrapper). */
void dispatch_state_entry_event_8(void) {
    D_80016000->unk_20->callback_084(0);
}
