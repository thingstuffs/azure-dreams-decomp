#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"

extern void func_800C3B7C(void *, s32, s32);
extern s32 D_800D6EFC[];

/*
 * Initializes entries from D_800D6EFC, clears the indexed object slot, and installs func_800C3B7C
 * with count 28.
 */
void initialize_scene_entry_group_28(void *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D6EFC);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800C3B7C;
    *(s16 *)((u8 *)object + 0x6C) = 28;
}
