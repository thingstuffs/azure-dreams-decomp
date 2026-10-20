#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D6568[];
extern u8 D_800D6570[];
extern u8 D_800D6598[];
extern u8 D_800D65A0[];

void initialize_scene_slot_11(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 11, (s32)D_800D6598, (s32)D_800D65A0, (s32)D_800D6568, (s32)D_800D6570);
}
