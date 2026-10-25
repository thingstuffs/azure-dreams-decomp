#include "common.h"
#include "town/person.h"

extern u8 D_800D7B80[];
extern u8 D_800D7B88[];
extern u8 D_800D7BB0[];
extern u8 D_800D7BB4[];

/* Registers the object in scene slot 7 using the four local setup tables. */
void initialize_scene_slot_7(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 7, D_800D7BB0, D_800D7BB4, D_800D7B80, D_800D7B88);
}
