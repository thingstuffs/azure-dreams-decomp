#include "common.h"
#include "town/person.h"

extern u8 D_800D600C[];
extern u8 D_800D6014[];
extern u8 D_800D603C[];
extern u8 D_800D6048[];

/* Registers the object in scene slot 4 using the four local setup tables. */
void initialize_scene_slot_4(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 4, D_800D603C, D_800D6048, D_800D600C, D_800D6014);
}
