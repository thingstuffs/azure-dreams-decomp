/* Reset object handler field 6c value 15 46ee4. */
#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3FC8;
#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"


/*
 * Reinitializes entries from linked data offset 0x1C, clears the indexed object slot, and installs
 * D_800C3FC8 with count 0x15.
 */
void reset_object_handler_field_6c_value_15_46ee4(TownObjectRecord *object, s32 unused, SpriteFrameState *updateValue) {
    PersonDescriptor *descriptor;

    descriptor = object->descriptor;
    initialize_object_entries(object, updateValue, descriptor->entries[7]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &D_800C3FC8;
    object->timer.as_s16 = 0x15;
}
