#include "common.h"
#include "town/person.h"

extern u8 D_800D74F8[];
extern u8 D_800D7500[];
extern u8 D_800D7528[];
extern u8 D_800D752C[];

/*
 * Registers the object in scene slot 58 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_58(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 58, D_800D7528, D_800D752C, D_800D74F8, D_800D7500);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
