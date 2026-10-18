/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80091D6C;
extern s32 D_800D00E0;

void func_800941D8(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D00E0, record, ptr2);
    record->unk_00.as_pm = &D_80091D6C;
    record->unk_0A.as_s16 = 0x15;
}
