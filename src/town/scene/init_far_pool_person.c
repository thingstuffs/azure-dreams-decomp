#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D7A98[];
extern u8 D_800D7AA0[];
extern u8 D_800D7AC8[];
extern u8 D_800D7ACC[];

/* Registers the object in scene slot 9 using the four local setup tables. */
void init_fur_pool_person(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 9, D_800D7AC8, D_800D7ACC, D_800D7A98, D_800D7AA0);
}
