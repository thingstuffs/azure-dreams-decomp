#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "town/person/state_updates.h"

extern s32 primary_reaction_entries[];
extern u8 D_800CA020[];


/* Initializes entries from D_800D64DC and installs D_800CA020 as the actor handler. */
void initialize_actor_primary_handler(TownObjectRecord *actor, ObjectPosition *unused, SpriteFrameState *sprite) {
    initialize_object_entries(actor, sprite, primary_reaction_entries);
    actor->handler = D_800CA020;
}
