#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"
#include "town/system.h"

extern s32 D_800D6EFC[];

/*
 * Initializes entries from D_800D6EFC, clears the indexed object slot, and installs func_800C3B7C
 * with count 28.
 */
void init_countdown_entry_group_28(struct TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *output)
{
    initialize_object_entries(object, output, D_800D6EFC);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = run_setup_on_timer_expiry;
    object->timer = 28;
}
