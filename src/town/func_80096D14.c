/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80090E78;
extern s32 D_800D0118;

/* Selects D_800D0118 and installs D_80090E78 with action count 6. */
void initialize_action_handler_with_count_six(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0118, record, ptr2);
    record->unk_00.as_pm = &D_80090E78;
    record->unk_0A.as_s16 = 6;
}
