#include "common.h"
#include "shared/object_index_slots.h"

extern void initialize_object_entries(void *, s8 *, s32 *);
extern void func_800C899C(void *, s32, s32);
extern s32 D_800D62BC[];

void initialize_scene_entry_group_8(void *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D62BC);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800C899C;
    *(s16 *)((u8 *)object + 0x6C) = 8;
}
