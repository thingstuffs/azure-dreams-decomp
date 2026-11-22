#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3A98;
#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object.h"

// Updates an object using its linked data, then resets its indexed flag and state.
void reset_object_handler_after_update(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *output) {
    PersonDescriptor *descriptor;

    descriptor = object->descriptor;
    initialize_object_entries(object, output, descriptor->entries[2]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &D_800C3A98;
    object->timer = 0x20;
}
