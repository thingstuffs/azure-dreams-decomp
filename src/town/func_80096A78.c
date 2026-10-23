/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80091D6C;

/* Selects D_800D00E0 and installs D_80091D6C with action count 0x15. */
void init_actor_action_state(Rec_func_80094268_arg0 *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D00E0, record, handler_context);
    record->unk_00.as_pm = &D_80091D6C;
    record->unk_0A.as_s16 = 0x15;
}
