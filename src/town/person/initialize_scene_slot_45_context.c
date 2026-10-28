#include "common.h"
#include "town/person.h"






/* Registers the object in scene slot 45 using the four local setup tables. */
void initialize_scene_slot_45_context(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 45, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
}
