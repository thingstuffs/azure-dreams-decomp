#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7A98[];
extern u8 D_800D7AA0[];
extern u8 D_800D7AC8[];
extern u8 D_800D7ACC[];

void initialize_scene_slot_9(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 9, (s32)D_800D7AC8, (s32)D_800D7ACC, (s32)D_800D7A98, (s32)D_800D7AA0);
}
