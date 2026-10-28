#include "common.h"
#include "town/person/object_slots.h"
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"

extern void * create_owner_following_sprite(void *state_value);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9, set its data pointers, and create its display object. */
void initialize_object_slot_9_and_display(void *object, void *unused_a, struct SpriteFrameState *unused_b) {
    initialize_object_and_register_slot(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    set_linked_data_pointers_variant_1(object, unused_a, unused_b);
    create_owner_following_sprite(object);
}
