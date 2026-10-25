#include "common.h"
#include "town/person.h"

extern u8 D_800D793C[];
extern u8 D_800D7944[];
extern u8 D_800D796C[];
extern u8 D_800D7970[];

/* Registers the object in scene slot 12 using the four local setup tables. */
void initialize_scene_slot_12(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 12, D_800D796C, D_800D7970, D_800D793C, D_800D7944);
}
