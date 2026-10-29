#include "town/person.h"
#include "shared/object_index_slots.h"
#include "town/person/object.h"

/* Select descriptor list +0x0C, clear its slot, and start the timed handler. */
void reset_person_descriptor_entries(PersonObject *object, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(object, output, object->descriptor->entries[3]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = decrement_object_timer_and_update;
    object->timer = 0x15;
}
