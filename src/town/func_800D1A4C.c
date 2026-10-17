#include "common.h"
#include "shared/object_index_slots.h"

extern void townInitializeObjectEntries(void *, s8 *, s32 *);
extern void func_800C3BB8(void *);
extern s32 D_800D77B0[];

void initialize_scene_entry_group_13(void *object, s32 unused, void *output)
{
    townInitializeObjectEntries(object, output, D_800D77B0);
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800C3BB8;
    *(s16 *)((u8 *)object + 0x6C) = 13;
}
