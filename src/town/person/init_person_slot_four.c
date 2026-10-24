#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D60C0[], D_800D60C4[], D_800D6090[], D_800D6098[];

/* Register slot four with its four fixed descriptor pointers. */
void init_person_slot_four(PersonObject *object) {
    initialize_object_and_register_slot(object, 4, D_800D60C0, D_800D60C4, D_800D6090, D_800D6098);
}
