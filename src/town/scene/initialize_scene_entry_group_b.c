#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"

extern void func_800C68E0(void *, s32, s32);
extern s32 D_800D58E0[];

/*
 * Initializes entries from D_800D58E0, clears the indexed object slot, and installs func_800C68E0
 * with count 9.
 */
void initialize_scene_entry_group_9(struct TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *output)
{
    initialize_object_entries(object, output, D_800D58E0);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = func_800C68E0;
    object->timer = 9;
}
