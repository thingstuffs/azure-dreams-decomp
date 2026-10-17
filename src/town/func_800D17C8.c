#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D74F8[];
extern u8 D_800D7500[];
extern u8 D_800D7528[];
extern u8 D_800D752C[];

void initialize_scene_slot_58(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 58, (s32)D_800D7528, (s32)D_800D752C, (s32)D_800D74F8, (s32)D_800D7500);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
