#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D63BC[];
extern u8 D_800D63C4[];
extern u8 D_800D63EC[];
extern u8 D_800D63F0[];

/* Registers the object in scene slot 59 using the four local setup tables. */
void initialize_scene_slot_59_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 59, (s32)D_800D63EC, (s32)D_800D63F0, (s32)D_800D63BC, (s32)D_800D63C4);
}
