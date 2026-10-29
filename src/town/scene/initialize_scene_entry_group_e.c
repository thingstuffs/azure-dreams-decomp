#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"

extern void func_800CC8AC(void *, void *, s32);
extern s32 D_800D6E7C[];

/*
 * Initializes entries from D_800D6E7C, clears the indexed object slot, and installs func_800CC8AC
 * with count 300.
 */
void initialize_scene_entry_group_300(void *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D6E7C);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800CC8AC;
    *(s16 *)((u8 *)object + 0x6C) = 300;
}
