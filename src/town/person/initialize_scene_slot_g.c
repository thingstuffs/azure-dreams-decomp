#include "common.h"
#include "town/person.h"

extern u8 D_800D739C[];
extern u8 D_800D73A4[];
extern u8 D_800D73CC[];
extern u8 D_800D73D0[];

/*
 * Registers the object in scene slot 60 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_60(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 60, D_800D73CC, D_800D73D0, D_800D739C, D_800D73A4);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
