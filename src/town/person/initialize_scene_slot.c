#include "common.h"
#include "town/person.h"

extern u8 D_800D6770[];
extern u8 D_800D6778[];
extern u8 D_800D67A0[];
extern u8 D_800D67A4[];

/* Registers the object in scene slot 18 using the four local setup tables. */
void initialize_scene_slot_18(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 18, D_800D67A0, D_800D67A4, D_800D6770, D_800D6778);
}
