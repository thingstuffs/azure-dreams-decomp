#include "town/person.h"
#include "shared/object_index_slots.h"
#include "town/person/object.h"

/* Select descriptor list +0x1C, clear its slot, and start the ten-update scale animation. */
void start_person_scale_animation(TownObjectRecord *object, ObjectPosition *unused, SpriteFrameState *output) {
    initialize_object_entries(object, output, object->descriptor->entries[7]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = animate_scale_and_restore;
    object->timer = 10;
}
