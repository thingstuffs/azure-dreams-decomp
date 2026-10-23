#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6490[];
extern u8 D_800D6498[];
extern u8 D_800D64C0[];
extern u8 D_800D64C4[];

/* Registers the object in scene slot 68 using the four local setup tables. */
void initialize_scene_slot_68(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 68, (s32)D_800D64C0, (s32)D_800D64C4, (s32)D_800D6490, (s32)D_800D6498);
}
