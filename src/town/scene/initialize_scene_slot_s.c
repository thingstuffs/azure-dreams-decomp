#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D793C[];
extern u8 D_800D7944[];
extern u8 D_800D796C[];
extern u8 D_800D7970[];

/* Registers the object in scene slot 12 using the four local setup tables. */
void initialize_scene_slot_12(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 12, D_800D796C, D_800D7970, D_800D793C, D_800D7944);
}
