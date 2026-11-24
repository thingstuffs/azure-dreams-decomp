#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"


/* Register person slot 81 with its four data tables. */
void init_person_slot_81(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    register_object_slot_with_tables(object, 81, slot_81_first_registration_table, slot_81_second_registration_table, slot_81_first_source_table, slot_81_second_source_table);
}
