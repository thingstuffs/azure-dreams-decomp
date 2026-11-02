/* Reset object handler field 6c value 15. */
#include "common.h"
#include "town/system/object_hooks.h"
#include "shared/object_index_slots.h"

#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"


void reset_object_handler_field_6c_value_15(TownObjectRecord *object, s32 unused, SpriteFrameState *updateValue) {
    PersonDescriptor *descriptor;

    descriptor = object->descriptor;
    func_800C2E84(object, updateValue, descriptor->entries[4]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &person_countdown_update_address;
    object->timer.as_s16 = 0x15;
}
