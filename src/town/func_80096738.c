/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_800911D4;
extern s32 D_800D0168;

void init_input_action_fallback(s32 **record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0168, (Rec_func_80094268_arg0 *) record, handler_context);
    *record = &D_800911D4;
}
