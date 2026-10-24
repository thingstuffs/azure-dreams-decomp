#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D6C7C[], D_800D6C80[], D_800D6C4C[], D_800D6C54[];

/* Register slot 33 with its four fixed descriptor pointers. */
void init_person_slot_thirty_three(PersonObject *object) {
    initialize_object_and_register_slot(object, 33, D_800D6C7C, D_800D6C80, D_800D6C4C, D_800D6C54);
}
