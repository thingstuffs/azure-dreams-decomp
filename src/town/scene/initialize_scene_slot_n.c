#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6E90[];
extern u8 D_800D6E98[];
extern u8 D_800D6EC0[];
extern u8 D_800D6EC4[];

/* Registers the object in scene slot 1 using the four local setup tables. */
void initialize_scene_slot_1(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 1, (s32)D_800D6EC0, (s32)D_800D6EC4, (s32)D_800D6E90, (s32)D_800D6E98);
}
