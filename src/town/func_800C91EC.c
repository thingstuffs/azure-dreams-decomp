#include "common.h"
#include "shared/object_index_slots.h"

extern void townInitializeObjectEntries(void *, s8 *, s32 *);
extern void func_800C68E0(void *, s32, s32);
extern s32 D_800D58E0[];

void initialize_scene_entry_group_9(void *object, s32 unused, void *output)
{
    townInitializeObjectEntries(object, output, D_800D58E0);
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800C68E0;
    *(s16 *)((u8 *)object + 0x6C) = 9;
}
