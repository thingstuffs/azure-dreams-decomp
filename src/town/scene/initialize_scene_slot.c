#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5A50[];
extern u8 D_800D5A58[];
extern u8 D_800D5A80[];
extern u8 D_800D5A84[];

/* Registers the object in scene slot 15 using the four local setup tables. */
void initialize_scene_slot_15(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 15, (s32)D_800D5A80, (s32)D_800D5A84, (s32)D_800D5A50, (s32)D_800D5A58);
}
