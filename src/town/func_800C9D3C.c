#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5E80[];
extern u8 D_800D5E88[];
extern u8 D_800D5EB0[];
extern u8 D_800D5EB4[];

void initialize_scene_slot_60_context(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 60, (s32)D_800D5EB0, (s32)D_800D5EB4, (s32)D_800D5E80, (s32)D_800D5E88);
}
