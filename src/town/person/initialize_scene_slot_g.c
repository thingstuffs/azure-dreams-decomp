#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D739C[];
extern u8 D_800D73A4[];
extern u8 D_800D73CC[];
extern u8 D_800D73D0[];

void initialize_scene_slot_60(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 60, (s32)D_800D73CC, (s32)D_800D73D0, (s32)D_800D739C, (s32)D_800D73A4);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
