#include "common.h"
#include "town/person.h"

extern u8 D_800D63BC[];
extern u8 D_800D63C4[];
extern u8 D_800D63EC[];
extern u8 D_800D63F0[];

/* Registers the object in scene slot 31 using the four local setup tables. */
void initialize_scene_slot_31(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 31, D_800D63EC, D_800D63F0, D_800D63BC, D_800D63C4);
}
