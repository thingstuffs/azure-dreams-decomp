#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D76C8[];
extern u8 D_800D76D0[];
extern u8 D_800D76F8[];
extern u8 D_800D76FC[];

void initialize_scene_slot_47(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 47, (s32)D_800D76F8, (s32)D_800D76FC, (s32)D_800D76C8, (s32)D_800D76D0);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
