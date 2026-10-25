#include "common.h"
#include "town/person.h"

extern u8 D_800D7B0C[];
extern u8 D_800D7B14[];
extern u8 D_800D7B3C[];
extern u8 D_800D7B40[];

/* Registers the object in scene slot 13 using the four local setup tables. */
void initialize_scene_slot_13(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 13, D_800D7B3C, D_800D7B40, D_800D7B0C, D_800D7B14);
}
