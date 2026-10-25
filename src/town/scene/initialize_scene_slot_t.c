#include "common.h"
#include "town/person.h"

extern u8 D_800D7A24[];
extern u8 D_800D7A2C[];
extern u8 D_800D7A54[];
extern u8 D_800D7A58[];

/* Registers the object in scene slot 8 using the four local setup tables. */
void initialize_scene_slot_8(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 8, D_800D7A54, D_800D7A58, D_800D7A24, D_800D7A2C);
}
