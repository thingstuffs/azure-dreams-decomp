/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/object.h"
#include "town/person_callbacks_api.h"

extern s32 primary_reaction_entries[];

extern s8 D_800826B8;


/* Initializes entries from D_800D64DC, clears D_800826B8, and installs D_800C9FBC with count eight. */
void start_reaction_raise(TownObjectRecord *actor, struct ObjectPosition *unused_position, SpriteFrameState *output) {
    initialize_object_entries(actor, output, primary_reaction_entries);
    D_800826B8 = 0;
    actor->handler = raise_reaction_output_until_expiry;
    actor->timer = 0x8;
}
