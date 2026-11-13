/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_handler.h"
#include "town.h"

extern s32 D_8009221C;

/* Selects action_object_handler_table and installs D_8009221C. */
void initialize_action_object(s32 **record, void *ptr, void *ptr2) {
    dispatch_selected_entry_if_nonzero(action_object_handler_table, (TownObjectRecord *) record, ptr2);
    *record = &D_8009221C;
}
