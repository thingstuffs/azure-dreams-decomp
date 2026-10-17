#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D63BC[];
extern u8 D_800D63C4[];
extern u8 D_800D63EC[];
extern u8 D_800D63F0[];

void initialize_scene_slot_31(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 31, (s32)D_800D63EC, (s32)D_800D63F0, (s32)D_800D63BC, (s32)D_800D63C4);
}
