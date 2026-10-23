#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D79B0[];
extern u8 D_800D79B8[];
extern u8 D_800D79E0[];
extern u8 D_800D79E4[];

/* Registers the object in scene slot 11 using the four local setup tables. */
void initialize_scene_slot_11_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 11, (s32)D_800D79E0, (s32)D_800D79E4, (s32)D_800D79B0, (s32)D_800D79B8);
}
