#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6770[];
extern u8 D_800D6778[];
extern u8 D_800D67A0[];
extern u8 D_800D67A4[];

void initialize_scene_slot_18(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 18, (s32)D_800D67A0, (s32)D_800D67A4, (s32)D_800D6770, (s32)D_800D6778);
}
