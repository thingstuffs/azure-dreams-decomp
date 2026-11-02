#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person.h"

/* Apply descriptor setup, clear the indexed flag, and reset the object callback and state. */
void apply_descriptor_setup_clear_indexed(TownObjectRecord *object, s32 unused, void *setup_context) {
    initialize_object_entries(object, setup_context, object->descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = (void *) apply_object_setup_update;
    object->heading.as_s16 = 0;
}
