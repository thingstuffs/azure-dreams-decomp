/* Recovered retail twin. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"
#include "town/player/motion.h"




/*
 * Selects the linked handler table, clears the indexed object slot, and installs D_800999AC with
 * count 0x20.
 */
void init_negative_x_step_action(TownObjectRecord *object, void *unused, void *handler_context) {
    dispatch_selected_entry_if_nonzero(object->handler_entries[6], object, handler_context);
    object_index_slots[object->index_slot].motion_id = 0;
    object->unk_04 = step_actor_minus_x_for_timer;
    object->unk_0A = 0x20;
}
