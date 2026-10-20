#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D67AC[];
extern u8 D_800D67B4[];
extern u8 D_800D67DC[];
extern u8 D_800D67E0[];

void initialize_scene_slot_18_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 18, (s32)D_800D67DC, (s32)D_800D67E0, (s32)D_800D67AC, (s32)D_800D67B4);
}
