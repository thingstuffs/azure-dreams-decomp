#include "town/person.h"
#include "shared/object_index_slots.h"
#include "town/person/object_setup.h"

/* Select descriptor list +0x14, clear the slot, and set heading 0xC00. */
void reset_person_heading_c00(PersonObject *object, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(object, output, object->descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = apply_object_setup_update;
    object->heading = 0xC00;
}
