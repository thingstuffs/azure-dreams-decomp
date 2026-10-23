#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D773C[];
extern u8 D_800D7744[];
extern u8 D_800D776C[];
extern u8 D_800D7770[];

/*
 * Registers the object in scene slot 52 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_52(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 52, (s32)D_800D776C, (s32)D_800D7770, (s32)D_800D773C, (s32)D_800D7744);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
