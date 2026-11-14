/* Reset object handler field 6c value 15. */
#include "common.h"
#include "town/system/object_hooks.h"
#include "shared/object_index_slots.h"

#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"
#include "town/system.h"


void restart_person_countdown_update(TownObjectRecord *object, s32 unused, SpriteFrameState *updateValue) {
    PersonDescriptor *descriptor;

    descriptor = object->descriptor;
    initialize_object_entries(object, updateValue, descriptor->entries[4]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = run_setup_on_timer_expiry;
    object->timer = 0x15;
}
