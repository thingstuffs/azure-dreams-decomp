#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7BF4[];
extern u8 D_800D7BFC[];
extern u8 D_800D7C24[];
extern u8 D_800D7C28[];

void initialize_scene_slot_6(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 6, (s32)D_800D7C24, (s32)D_800D7C28, (s32)D_800D7BF4, (s32)D_800D7BFC);
}
