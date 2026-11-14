#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D7A24[];
extern u8 D_800D7A2C[];
extern u8 D_800D7A54[];
extern u8 D_800D7A58[];

/* Registers the object in scene slot 8 using the four local setup tables. */
void initialize_scene_slot_8(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 8, D_800D7A54, D_800D7A58, D_800D7A24, D_800D7A2C);
}
