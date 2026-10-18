/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80090D44;
extern s32 D_800D0080;

void func_80093DD8(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0080, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80090D44;
}
