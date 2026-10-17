#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D66E8[];
extern u8 D_800D66F0[];
extern u8 D_800D6718[];
extern u8 D_800D671C[];

void initialize_scene_slot_45_context(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 45, (s32)D_800D6718, (s32)D_800D671C, (s32)D_800D66E8, (s32)D_800D66F0);
}
