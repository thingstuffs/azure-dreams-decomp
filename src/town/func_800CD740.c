#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6824[];
extern u8 D_800D682C[];
extern u8 D_800D6854[];
extern u8 D_800D6858[];

void initialize_scene_slot_57_context(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 57, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}
