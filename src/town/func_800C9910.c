#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5D18[];
extern u8 D_800D5D20[];
extern u8 D_800D5D48[];
extern u8 D_800D5D4C[];

void initialize_scene_slot_3(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 3, (s32)D_800D5D48, (s32)D_800D5D4C, (s32)D_800D5D18, (s32)D_800D5D20);
}
