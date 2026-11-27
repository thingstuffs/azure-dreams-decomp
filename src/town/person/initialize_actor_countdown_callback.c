#include "common.h"
#include "town/system/object_hooks.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"


#include "town/person/object/initialize_object_entries_api.h"
#include "town/person.h"
extern s32 countdown_object_heading_entries[];


/* Initialize the actor state, clear its entry flag, and set a callback with a 32-tick countdown. */
void initialize_actor_countdown_callback(TownObjectRecord *actor_arg, ObjectPosition *unused_position, SpriteFrameState *sprite) {
    TownObjectRecord *actor = actor_arg;

    initialize_object_entries(actor_arg, sprite, countdown_object_heading_entries);
    object_index_slots[actor->slot].motion_id = 0;
    actor->handler = &person_countdown_update_address;
    actor->timer = 0x20;
}
