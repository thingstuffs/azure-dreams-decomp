#include "common.h"
#include "town/person.h"

extern void set_linked_data_pointers_variant_1(void *record, s32 first_value, s32 second_value);
extern void create_owner_following_sprite(void *state_value);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9, set its data pointers, and create its display object. */
void initialize_object_slot_9_and_display(void *object, s32 unused_a, s32 unused_b) {
    initialize_object_and_register_slot(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    set_linked_data_pointers_variant_1(object, unused_a, unused_b);
    create_owner_following_sprite(object);
}
