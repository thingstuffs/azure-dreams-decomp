#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7654[];
extern u8 D_800D765C[];
extern u8 D_800D7684[];
extern u8 D_800D7688[];

void initialize_scene_slot_48(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 48, (s32)D_800D7684, (s32)D_800D7688, (s32)D_800D7654, (s32)D_800D765C);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
