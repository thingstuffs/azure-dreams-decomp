#include "common.h"
#include "town/person.h"






/* Registers the object in scene slot 45 using the four local setup tables. */
void initialize_scene_slot_45_context(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 45, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
}
