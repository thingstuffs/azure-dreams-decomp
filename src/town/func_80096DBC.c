/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_800927EC;
extern s32 D_800D0128;

void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0128, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_800927EC;
}
