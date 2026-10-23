/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80090DF0;
extern s32 player_interaction_handler_entries;

void init_unchanged_action_fallback(s32 **record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) &player_interaction_handler_entries, (Rec_func_80094268_arg0 *) record, handler_context);
    *record = &D_80090DF0;
}
