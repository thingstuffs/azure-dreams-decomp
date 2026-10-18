#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D78C8[];
extern u8 D_800D78D0[];
extern u8 D_800D78F8[];
extern u8 D_800D78FC[];

void initialize_scene_slot_10(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 10, (s32)D_800D78F8, (s32)D_800D78FC, (s32)D_800D78C8, (s32)D_800D78D0);
}
