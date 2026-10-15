/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_800911D4;
extern s32 D_800D0168;

void func_80093E98(s32 **record, void *ptr, void *ptr2) {
    func_80094984((s32 *) &D_800D0168, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_800911D4;
}
