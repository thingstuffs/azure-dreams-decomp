/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_8009221C;
extern s32 D_800D00B8;

void initialize_action_object(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D00B8, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_8009221C;
}
