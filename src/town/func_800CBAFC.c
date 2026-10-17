#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6490[];
extern u8 D_800D6498[];
extern u8 D_800D64C0[];
extern u8 D_800D64C4[];

void initialize_scene_slot_68(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 68, (s32)D_800D64C0, (s32)D_800D64C4, (s32)D_800D6490, (s32)D_800D6498);
}
