#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5EF4[];
extern u8 D_800D5EFC[];
extern u8 D_800D5F24[];
extern u8 D_800D5F28[];

void initialize_scene_slot_42_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 42, (s32)D_800D5F24, (s32)D_800D5F28, (s32)D_800D5EF4, (s32)D_800D5EFC);
}
