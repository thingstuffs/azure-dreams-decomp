#include "common.h"

extern void initialize_object_and_register_slot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D7410[];
extern u8 D_800D7418[];
extern u8 D_800D7440[];
extern u8 D_800D7444[];

/*
 * Registers the object in scene slot 59 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_59(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 59, (s32)D_800D7440, (s32)D_800D7444, (s32)D_800D7410, (s32)D_800D7418);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
