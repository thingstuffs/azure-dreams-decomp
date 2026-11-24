#include "town/person/object.h"
#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"

void initialize_countdown_expiry_entry_group(TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *output)
{
    initialize_object_entries(object, output, countdown_expiry_entry_group);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = run_record_countdown_expiry;
    object->timer = 5;
}
