#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"
#include "town/person/motion_callbacks_api.h"


extern s32 D_800D6DA8[];

/*
 * Initializes entries from D_800D6DA8, clears the indexed object slot, and installs func_800CC644
 * with count 120.
 */
void initialize_offset_target_entry_group(void *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D6DA8);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = move_toward_offset_target;
    *(s16 *)((u8 *)object + 0x6C) = 120;
}
