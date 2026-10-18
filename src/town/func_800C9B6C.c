#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5DD4[];
extern u8 D_800D5DDC[];
extern u8 D_800D5E04[];
extern u8 D_800D5E08[];

void initialize_scene_slot_55(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 55, (s32)D_800D5E04, (s32)D_800D5E08, (s32)D_800D5DD4, (s32)D_800D5DDC);
}
