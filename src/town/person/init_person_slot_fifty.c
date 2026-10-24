#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D71F4[], D_800D71F8[], D_800D71C4[], D_800D71CC[];

/* Register slot 50 with its four fixed descriptor pointers. */
void init_person_slot_fifty(PersonObject *object) {
    initialize_object_and_register_slot(object, 50, D_800D71F4, D_800D71F8, D_800D71C4, D_800D71CC);
}
