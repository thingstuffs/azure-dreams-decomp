#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7C7C[];
extern u8 D_800D7C84[];
extern u8 D_800D7CAC[];
extern u8 D_800D7CB0[];

void initialize_scene_slot_37(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 37, (s32)D_800D7CAC, (s32)D_800D7CB0, (s32)D_800D7C7C, (s32)D_800D7C84);
}
