#include "town/person.h"

/* Register person slot 51 with its four data tables. */
void init_person_slot_fifty_one(PersonObject *object) {
    initialize_object_and_register_slot(object, 51, D_800D5270, D_800D5274, D_800D5240, D_800D5248);
}
