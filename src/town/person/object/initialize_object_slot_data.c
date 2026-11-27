#include "common.h"
#include "town/person/object_slots.h"
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"
#include "town/person/object.h"


extern u8 fur_animation_lists[];
extern u8 fur_descriptor[];
extern u8 fur_state_handlers[];
extern u8 fur_script_action_handlers[];

/* Initialize object slot 9 and set its data pointers. */
void init_fur_person(TownObjectRecord *object, ObjectPosition *unused_1, struct SpriteFrameState *unused_2) {
    register_object_slot_with_tables(object, 9, fur_state_handlers, fur_script_action_handlers, fur_animation_lists,
                  fur_descriptor);
    set_object_referenced_data_pointers(object, unused_1, unused_2);
}
