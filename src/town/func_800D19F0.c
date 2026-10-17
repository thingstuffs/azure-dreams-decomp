#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D773C[];
extern u8 D_800D7744[];
extern u8 D_800D776C[];
extern u8 D_800D7770[];

void initialize_scene_slot_52(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 52, (s32)D_800D776C, (s32)D_800D7770, (s32)D_800D773C, (s32)D_800D7744);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
