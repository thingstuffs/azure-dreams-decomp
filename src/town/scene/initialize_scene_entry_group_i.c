#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"
#include "town/system.h"

extern s32 D_800D77B8[];

/*
 * Initializes entries from D_800D77B8, clears the indexed object slot, and installs func_800C3B7C
 * with count 4.
 */
void initialize_scene_entry_group_4(TownObjectRecord *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D77B8);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = func_800C3B7C;
    object->timer = 4;
}
