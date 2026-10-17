#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6F74[];
extern u8 D_800D6F7C[];
extern u8 D_800D6FA4[];
extern u8 D_800D6FA8[];

void initialize_scene_slot_12_context(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 12, (s32)D_800D6FA4, (s32)D_800D6FA8, (s32)D_800D6F74, (s32)D_800D6F7C);
}
