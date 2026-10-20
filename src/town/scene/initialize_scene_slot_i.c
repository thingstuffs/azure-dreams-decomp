#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D600C[];
extern u8 D_800D6014[];
extern u8 D_800D603C[];
extern u8 D_800D6048[];

void initialize_scene_slot_4(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 4, (s32)D_800D603C, (s32)D_800D6048, (s32)D_800D600C, (s32)D_800D6014);
}
