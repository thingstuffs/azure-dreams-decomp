#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s32 D_800D54BC[];


/* Initialize the actor, clear its table flag, and install its handler. */
void initialize_actor_clear_table_flag(TownObjectRecord *actor, ObjectPosition *unused_position, SpriteFrameState *sprite) {
    initialize_object_entries(actor, sprite, D_800D54BC);
    object_index_slots[actor->slot].motion_id = 0;
    actor->handler = &reset_object_entries_on_flag_bits;
}
