#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"

   /* ((TownObjectRecord *)arg0)->unk_80 in set_object_heading_and_apply_setup */

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"

/* Clears the object's table flag and resets its animation before updating it. */
void set_object_heading_and_apply_setup(TownObjectRecord *object, void *position, void *anim_state) {
    initialize_object_entries(object, anim_state, object->descriptor->entries[1]);
    object_index_slots[object->slot].unk_00 = 0;
    object->heading = 0x200;
    apply_object_setup_and_update(object, position, anim_state);
}
