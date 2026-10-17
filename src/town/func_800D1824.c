#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D756C[];
extern u8 D_800D7574[];
extern u8 D_800D759C[];
extern u8 D_800D75A0[];

void initialize_scene_slot_45(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 45, (s32)D_800D759C, (s32)D_800D75A0, (s32)D_800D756C, (s32)D_800D7574);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
