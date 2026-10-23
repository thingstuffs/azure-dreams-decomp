#include "common.h"
#include "shared/object_index_slots.h"

extern void initialize_object_entries(void *, s8 *, s32 *);
extern void func_800C3BB8(void *);
extern s32 D_800D77B0[];

/*
 * Initializes entries from D_800D77B0, clears the indexed object slot, and installs func_800C3BB8
 * with count 13.
 */
void initialize_scene_entry_group_13(void *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D77B0);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800C3BB8;
    *(s16 *)((u8 *)object + 0x6C) = 13;
}
