#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D51C8[];
extern u8 D_800D51D0[];
extern u8 D_800D51F8[];
extern u8 D_800D51FC[];

void initialize_scene_slot_1_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 1, (s32)D_800D51F8, (s32)D_800D51FC, (s32)D_800D51C8, (s32)D_800D51D0);
}
