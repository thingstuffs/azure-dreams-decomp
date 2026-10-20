#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5AC8[];
extern u8 D_800D5AD0[];
extern u8 D_800D5AF8[];
extern u8 D_800D5AFC[];

void initialize_scene_slot_47_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 47, (s32)D_800D5AF8, (s32)D_800D5AFC, (s32)D_800D5AC8, (s32)D_800D5AD0);
}
