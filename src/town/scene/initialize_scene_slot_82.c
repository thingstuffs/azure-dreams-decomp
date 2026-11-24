#include "common.h"
#include "town/person.h"
#include "town/scene.h"


/* Registers the object in scene slot 82 with the setup tables of scene slot 31 (Jacof). */
void initialize_scene_slot_82(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 82, slot_31_first_registration_table, slot_31_second_registration_table, slot_31_first_source_table, slot_31_second_source_table);
}
