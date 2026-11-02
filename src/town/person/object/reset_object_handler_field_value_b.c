/* Reset object handler field 72 value 400. */
#include "common.h"
#include "shared/object_index_slots.h"

extern s32 person_reset_handler_address;
#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"


void reset_object_handler_field_72_value_400(TownObjectRecord *object, s32 unused, SpriteFrameState *updateValue) {
    PersonDescriptor *descriptor;

    descriptor = object->descriptor;
    func_800C2E84(object, updateValue, descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &person_reset_handler_address;
    object->heading.as_s16 = 0x400;
}
