/* Reset object handler field 72 value 800. */
#include "common.h"
#include "shared/object_index_slots.h"


#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"
#include "town/person/object_setup.h"


void reset_object_handler_field_72_value_800(TownObjectRecord *object, s32 unused, SpriteFrameState *updateValue) {
    PersonDescriptor *descriptor;

    descriptor = object->descriptor;
    initialize_object_entries(object, updateValue, descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = apply_object_setup_update;
    object->heading.as_s16 = 0x800;
}
