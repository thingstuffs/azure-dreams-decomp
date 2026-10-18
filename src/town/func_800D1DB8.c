#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7A24[];
extern u8 D_800D7A2C[];
extern u8 D_800D7A54[];
extern u8 D_800D7A58[];

void initialize_scene_slot_8(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 8, (s32)D_800D7A54, (s32)D_800D7A58, (s32)D_800D7A24, (s32)D_800D7A2C);
}
