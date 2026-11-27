#include "common.h"
#include "town/person/object_slots.h"
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"
#include "town/person/object.h"

extern u8 fur_animation_lists[];
extern u8 fur_descriptor[];
extern u8 fur_state_handlers[];
extern u8 fur_script_action_handlers[];

/* Initialize object slot 9, set its data pointers, and create its display object. */
void init_fur_with_follower_sprite(TownObjectRecord *object, ObjectPosition *unused_a, struct SpriteFrameState *unused_b) {
    register_object_slot_with_tables(object, 9, fur_state_handlers, fur_script_action_handlers, fur_animation_lists,
                  fur_descriptor);
    set_linked_data_pointers_variant_1(object, unused_a, unused_b);
    create_owner_following_sprite(object);
}
