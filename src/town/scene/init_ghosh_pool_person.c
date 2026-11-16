#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D7BF4[];
extern u8 D_800D7BFC[];
extern u8 D_800D7C24[];
extern u8 D_800D7C28[];

/* Registers the object in scene slot 6 using the four local setup tables. */
void init_ghosh_pool_person(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 6, D_800D7C24, D_800D7C28, D_800D7BF4, D_800D7BFC);
}
