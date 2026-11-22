#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
#include "town/person.h"
extern s32 D_800D5540[];

/* Initialize the actor with the state table and run its follow-up handler. */
void initialize_actor_state_table(TownObjectRecord *actor, ObjectPosition *position, SpriteFrameState *sprite) {
    initialize_object_entries(actor, sprite, D_800D5540);
    clear_record_indexed_flag(actor, position, sprite);
}
