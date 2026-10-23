/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_handler.h"

extern s32 tracked_actor_callback_address;

/* Selects movement_action_handler_table and installs tracked_actor_callback_address. */
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) movement_action_handler_table, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &tracked_actor_callback_address;
}
