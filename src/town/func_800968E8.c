/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80090F84;
extern s32 D_800D0160;

void func_80094048(s32 **record, void *ptr, void *ptr2) {
    func_80094984((s32 *) &D_800D0160, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80090F84;
}
