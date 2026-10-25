#include "common.h"
#include "town/person.h"

extern u8 D_800D5E80[];
extern u8 D_800D5E88[];
extern u8 D_800D5EB0[];
extern u8 D_800D5EB4[];

/* Registers the object in scene slot 60 using the four local setup tables. */
void initialize_scene_slot_60_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 60, D_800D5EB0, D_800D5EB4, D_800D5E80, D_800D5E88);
}
