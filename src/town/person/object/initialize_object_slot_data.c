#include "common.h"
#include "town/person/object_slots.h"
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"


extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9 and set its data pointers. */
void initialize_object_slot_9_data(void *object, void *unused_1, struct SpriteFrameState *unused_2) {
    initialize_object_and_register_slot(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    set_object_referenced_data_pointers(object, unused_1, unused_2);
}
