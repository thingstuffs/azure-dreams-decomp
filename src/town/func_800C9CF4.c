#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5E0C[];
extern u8 D_800D5E14[];
extern u8 D_800D5E3C[];
extern u8 D_800D5E40[];

void initialize_scene_slot_56(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 56, (s32)D_800D5E3C, (s32)D_800D5E40, (s32)D_800D5E0C, (s32)D_800D5E14);
}
