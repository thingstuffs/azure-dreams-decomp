#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"
#include "town/system.h"

extern s32 D_800D77B0[];

/*
 * Initializes entries from D_800D77B0, clears the indexed object slot, and installs func_800C3BB8
 * with count 13.
 */
void init_countdown_handler_entry_group(TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *output)
{
    initialize_object_entries(object, output, D_800D77B0);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = install_handler_on_timer_expiry;
    object->timer = 13;
}
