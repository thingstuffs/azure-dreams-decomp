#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5A50[];
extern u8 D_800D5A58[];
extern u8 D_800D5A80[];
extern u8 D_800D5A84[];

void initialize_scene_slot_15(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 15, (s32)D_800D5A80, (s32)D_800D5A84, (s32)D_800D5A50, (s32)D_800D5A58);
}
