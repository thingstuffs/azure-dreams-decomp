/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80092DA8;
extern s32 D_800D0148;

void initialize_threshold_interaction_object(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0148, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80092DA8;
}
