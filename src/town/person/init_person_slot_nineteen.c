#include "town/person.h"

/* Register person slot 19 with its four data tables. */
void init_person_slot_nineteen(PersonObject *object) {
    initialize_object_and_register_slot(object, 19, D_800D5478, D_800D547C, D_800D5448, D_800D5450);
}
