#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "town/person/state.h"

   /* ((TownObjectRecord *)arg0)->unk_80 in update_object_state_and_lookup */

#include "town/person/object/initialize_object_entries_api.h"                /* extern */
#include "town/person/object_setup.h"

/* Update the object's state, clear its indexed flag, and store the lookup result. */
void update_object_state_and_lookup(TownObjectRecord *object, void *lookup_key, void *state_value) {
    initialize_object_entries((object), state_value, object->descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &apply_object_setup_update;
    object->heading = get_cached_or_coordinate_transform_value(object, lookup_key);
}
