#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5BD8[];
extern u8 D_800D5BE0[];
extern u8 D_800D5C08[];
extern u8 D_800D5C0C[];

void initialize_scene_slot_6_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 6, (s32)D_800D5C08, (s32)D_800D5C0C, (s32)D_800D5BD8, (s32)D_800D5BE0);
}
