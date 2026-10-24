#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D57A4[], D_800D57A8[], D_800D5774[], D_800D577C[];

/* Register slot 35 with its four fixed descriptor pointers. */
void init_person_slot_thirty_five(PersonObject *object) {
    initialize_object_and_register_slot(object, 35, D_800D57A4, D_800D57A8, D_800D5774, D_800D577C);
}
