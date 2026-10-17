#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6E90[];
extern u8 D_800D6E98[];
extern u8 D_800D6EC0[];
extern u8 D_800D6EC4[];

void initialize_scene_slot_1(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 1, (s32)D_800D6EC0, (s32)D_800D6EC4, (s32)D_800D6E90, (s32)D_800D6E98);
}
