#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6824[];
extern u8 D_800D682C[];
extern u8 D_800D6854[];
extern u8 D_800D6858[];

void initialize_scene_slot_69(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 69, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}
