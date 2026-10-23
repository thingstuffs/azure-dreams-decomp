#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D793C[];
extern u8 D_800D7944[];
extern u8 D_800D796C[];
extern u8 D_800D7970[];

/* Registers the object in scene slot 12 using the four local setup tables. */
void initialize_scene_slot_12(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 12, (s32)D_800D796C, (s32)D_800D7970, (s32)D_800D793C, (s32)D_800D7944);
}
