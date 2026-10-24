#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D69B8[], D_800D69BC[], D_800D6988[], D_800D6990[];
extern void func_800CB028(PersonObject *, s32, s8 *);

/* Register slot 8 with its four fixed descriptor pointers. */
void init_person_slot_eight(PersonObject *object, s32 context, s8 *output) {
    initialize_object_and_register_slot(object, 8, D_800D69B8, D_800D69BC, D_800D6988, D_800D6990);
    func_800CB028(object, context, output);
}
