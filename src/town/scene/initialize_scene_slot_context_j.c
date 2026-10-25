#include "common.h"
#include "town/person.h"

extern u8 D_800D79B0[];
extern u8 D_800D79B8[];
extern u8 D_800D79E0[];
extern u8 D_800D79E4[];

/* Registers the object in scene slot 11 using the four local setup tables. */
void initialize_scene_slot_11_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 11, D_800D79E0, D_800D79E4, D_800D79B0, D_800D79B8);
}
