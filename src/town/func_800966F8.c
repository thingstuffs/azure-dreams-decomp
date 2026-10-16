/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80091114;
extern s32 D_800D0088;

void func_80093E58(s32 **record, void *ptr, void *ptr2) {
    townCallTheHandlerSelectsNonzeroEntry((s32 *) &D_800D0088, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80091114;
}
