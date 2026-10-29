#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D5D18[];
extern u8 D_800D5D20[];
extern u8 D_800D5D48[];
extern u8 D_800D5D4C[];

/* Registers the object in scene slot 3 using the four local setup tables. */
void initialize_scene_slot_3(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 3, D_800D5D48, D_800D5D4C, D_800D5D18, D_800D5D20);
}
