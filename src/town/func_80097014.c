/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80093328;

void init_timed_dispatch_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0120, record, handler_context);
    record->unk_00.as_pm = &D_80093328;
    record->unk_0A.as_s16 = 0xA;
}
