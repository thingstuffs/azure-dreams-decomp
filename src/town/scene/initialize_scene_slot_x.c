#include "common.h"
#include "town/person.h"

extern u8 D_800D7BF4[];
extern u8 D_800D7BFC[];
extern u8 D_800D7C24[];
extern u8 D_800D7C28[];

/* Registers the object in scene slot 6 using the four local setup tables. */
void initialize_scene_slot_6(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 6, D_800D7C24, D_800D7C28, D_800D7BF4, D_800D7BFC);
}
