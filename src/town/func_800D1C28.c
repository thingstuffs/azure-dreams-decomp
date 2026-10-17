#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D784C[];
extern u8 D_800D7854[];
extern u8 D_800D787C[];
extern u8 D_800D7880[];

void initialize_scene_slot_41(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 41, (s32)D_800D787C, (s32)D_800D7880, (s32)D_800D784C, (s32)D_800D7854);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
