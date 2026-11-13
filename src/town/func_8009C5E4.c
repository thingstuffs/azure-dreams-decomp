/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"
#include "town/data.h"


/*
 * Selects the table from the linked record, clears the indexed object slot, and installs
 * record_action_update_address with count 0x15.
 */
void start_record_action_countdown(TownObjectRecord *object, void *unused, void *handler_context) {
    dispatch_selected_entry_if_nonzero(object->handler_entries[3], object, handler_context);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04 = &record_action_update_address;
    object->unk_0A = 0x15;
}
