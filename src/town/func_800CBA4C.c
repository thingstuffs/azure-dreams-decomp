#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6430[];
extern u8 D_800D6438[];
extern u8 D_800D6460[];
extern u8 D_800D6464[];

void initialize_scene_slot_36(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 36, (s32)D_800D6460, (s32)D_800D6464, (s32)D_800D6430, (s32)D_800D6438);
}
