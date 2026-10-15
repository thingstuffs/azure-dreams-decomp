/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80092ECC;
extern s32 D_800D00B8;

void func_80094660(s32 **record, void *ptr, void *ptr2) {
    func_80094984((s32 *) &D_800D00B8, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80092ECC;
}
