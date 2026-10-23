/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_handler.h"

extern s32 town_radial_motion_address;

void initialize_action_callback_from_entry(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) action_object_handler_table, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &town_radial_motion_address;
}
