#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D75E0[];
extern u8 D_800D75E8[];
extern u8 D_800D7610[];
extern u8 D_800D7614[];

void initialize_scene_slot_62(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 62, (s32)D_800D7610, (s32)D_800D7614, (s32)D_800D75E0, (s32)D_800D75E8);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
