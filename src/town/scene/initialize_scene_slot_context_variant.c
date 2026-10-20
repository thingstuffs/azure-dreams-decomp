#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6DF8[];
extern u8 D_800D6E00[];
extern u8 D_800D6E28[];
extern u8 D_800D6E2C[];

void initialize_scene_slot_11_context_variant(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 11, (s32)D_800D6E28, (s32)D_800D6E2C, (s32)D_800D6DF8, (s32)D_800D6E00);
}
