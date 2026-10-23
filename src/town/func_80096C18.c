/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_handler.h"

extern s32 D_8009221C;

/* Selects action_object_handler_table and installs D_8009221C. */
void initialize_action_object(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) action_object_handler_table, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_8009221C;
}
