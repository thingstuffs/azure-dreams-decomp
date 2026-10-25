#include "common.h"
#include "town/person.h"

extern u8 D_800D77C0[];
extern u8 D_800D77C8[];
extern u8 D_800D77F0[];
extern u8 D_800D77F4[];

/*
 * Registers the object in scene slot 16 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_16(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 16, D_800D77F0, D_800D77F4, D_800D77C0, D_800D77C8);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
