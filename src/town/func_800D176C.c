#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7484[];
extern u8 D_800D748C[];
extern u8 D_800D74B4[];
extern u8 D_800D74B8[];

void initialize_scene_slot_84(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 84, (s32)D_800D74B4, (s32)D_800D74B8, (s32)D_800D7484, (s32)D_800D748C);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
