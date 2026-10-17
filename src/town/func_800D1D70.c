#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D79B0[];
extern u8 D_800D79B8[];
extern u8 D_800D79E0[];
extern u8 D_800D79E4[];

void initialize_scene_slot_11_context(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 11, (s32)D_800D79E0, (s32)D_800D79E4, (s32)D_800D79B0, (s32)D_800D79B8);
}
