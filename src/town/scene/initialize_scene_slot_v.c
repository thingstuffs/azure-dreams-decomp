#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D7B0C[];
extern u8 D_800D7B14[];
extern u8 D_800D7B3C[];
extern u8 D_800D7B40[];

/* Registers the object in scene slot 13 using the four local setup tables. */
void initialize_scene_slot_13(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 13, D_800D7B3C, D_800D7B40, D_800D7B0C, D_800D7B14);
}
