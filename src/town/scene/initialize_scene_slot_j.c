#include "common.h"
#include "town/person.h"
#include "town/scene.h"


/* Registers the object in scene slot 31 using the four local setup tables. */
void initialize_scene_slot_31(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 31, slot_31_first_registration_table, slot_31_second_registration_table, slot_31_first_source_table, slot_31_second_source_table);
}
