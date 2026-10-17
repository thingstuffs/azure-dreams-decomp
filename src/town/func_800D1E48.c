#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7B0C[];
extern u8 D_800D7B14[];
extern u8 D_800D7B3C[];
extern u8 D_800D7B40[];

void initialize_scene_slot_13(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 13, (s32)D_800D7B3C, (s32)D_800D7B40, (s32)D_800D7B0C, (s32)D_800D7B14);
}
