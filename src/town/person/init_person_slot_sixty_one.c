#include "town/person.h"

extern void initialize_object_and_register_slot(PersonObject *, s32, void *, void *, void *, void *);
extern u8 D_800D6718[], D_800D671C[], D_800D66E8[], D_800D66F0[];

/* Register slot 61 with its descriptor pointers and set output halfword +0x12. */
void init_person_slot_sixty_one(PersonObject *object, s32 unused, PersonOutput *output) {
    initialize_object_and_register_slot(object, 0x3D, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    output->unk_12 = 2;
}
