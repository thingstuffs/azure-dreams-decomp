#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D5478[], D_800D547C[], D_800D5448[], D_800D5450[];

/* Register slot 19 with its four fixed descriptor pointers. */
void init_person_slot_nineteen(PersonObject *object) {
    initialize_object_and_register_slot(object, 19, D_800D5478, D_800D547C, D_800D5448, D_800D5450);
}
