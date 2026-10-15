/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80090C68;
extern s32 D_800D0180;

void func_80093D90(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    func_80094984((s32 *) &D_800D0180, record, ptr2);
    record->unk_00.as_pm = &D_80090C68;
    record->unk_0A.as_s16 = 0x15;
}
