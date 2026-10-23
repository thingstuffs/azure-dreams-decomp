/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80090D44;
extern s32 D_800D0080;

/* Selects D_800D0080 and installs D_80090D44. */
void init_button_transition_action(s32 **record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0080, (Rec_func_80094268_arg0 *) record, handler_context);
    *record = &D_80090D44;
}
