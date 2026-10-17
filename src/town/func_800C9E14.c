#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5F68[];
extern u8 D_800D5F70[];
extern u8 D_800D5F98[];
extern u8 D_800D5F9C[];

void initialize_scene_slot_27(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 27, (s32)D_800D5F98, (s32)D_800D5F9C, (s32)D_800D5F68, (s32)D_800D5F70);
}
