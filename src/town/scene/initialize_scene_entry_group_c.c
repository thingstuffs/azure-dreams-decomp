#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"

extern void func_800C899C(void *, s32, s32);
extern s32 D_800D62BC[];

/*
 * Initializes entries from D_800D62BC, clears the indexed object slot, and installs func_800C899C
 * with count 8.
 */
void initialize_scene_entry_group_8(struct TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *output)
{
    initialize_object_entries(object, output, D_800D62BC);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = func_800C899C;
    object->timer = 8;
}
