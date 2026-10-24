#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D5270[], D_800D5274[], D_800D5240[], D_800D5248[];

/* Register slot 51 with its four fixed descriptor pointers. */
void init_person_slot_fifty_one(PersonObject *object) {
    initialize_object_and_register_slot(object, 51, D_800D5270, D_800D5274, D_800D5240, D_800D5248);
}
