#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 person_slot_reset_byte;
extern M2C_UNK D_800CE780;
extern s32 person_reaction_object_entries[];


/* Initialize the object, clear the global flag, and set its handler and initial offset. */
void initialize_object_with_handler_and_offset(TownObjectRecord *object, ObjectPosition *motion, void *init_data) {
    initialize_object_entries((Struct800C5724 *)(object), init_data, person_reaction_object_entries);
    person_slot_reset_byte = 0;
    object->handler = &D_800CE780;
    motion->velocity_z = 0xFFF60000;
}
