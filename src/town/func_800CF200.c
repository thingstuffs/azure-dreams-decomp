#include "common.h"
#include "shared/object_index_slots.h"

extern void townInitializeObjectEntries(void *, s8 *, s32 *);
extern void func_800CC8AC(void *, void *, s32);
extern s32 D_800D6E7C[];

void initialize_scene_entry_group_300(void *object, s32 unused, void *output)
{
    townInitializeObjectEntries(object, output, D_800D6E7C);
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = func_800CC8AC;
    *(s16 *)((u8 *)object + 0x6C) = 300;
}
