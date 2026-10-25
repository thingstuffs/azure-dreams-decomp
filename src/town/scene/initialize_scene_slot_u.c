#include "common.h"
#include "town/person.h"

extern u8 D_800D7A98[];
extern u8 D_800D7AA0[];
extern u8 D_800D7AC8[];
extern u8 D_800D7ACC[];

/* Registers the object in scene slot 9 using the four local setup tables. */
void initialize_scene_slot_9(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 9, D_800D7AC8, D_800D7ACC, D_800D7A98, D_800D7AA0);
}
