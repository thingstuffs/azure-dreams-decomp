#include "common.h"
#include "town/person.h"

extern u8 D_800D78C8[];
extern u8 D_800D78D0[];
extern u8 D_800D78F8[];
extern u8 D_800D78FC[];

/* Registers the object in scene slot 10 using the four local setup tables. */
void initialize_scene_slot_10(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 10, D_800D78F8, D_800D78FC, D_800D78C8, D_800D78D0);
}
