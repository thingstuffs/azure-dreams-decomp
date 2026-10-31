/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80091CE0;
extern s32 D_800D00D8;

/* Selects D_800D00D8 and installs D_80091CE0 with action count 1. */
void init_countdown_handler_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry(&D_800D00D8, record, handler_context);
    record->unk_00.as_pm = &D_80091CE0;
    record->unk_0A.as_s16 = 1;
}
