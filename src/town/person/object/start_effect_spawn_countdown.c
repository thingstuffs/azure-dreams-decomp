#include "town/person/object.h"
#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "town/system/object_hooks.h"
#include "shared/town_object.h"

#include "shared/object_index_slots.h"


/* Load the object's entries, clear its index slot, and spawn the effect after 21 updates. */
void start_effect_spawn_countdown(TownObjectRecord *actor, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(actor, output, effect_spawn_countdown_entries);
    object_index_slots[actor->slot].unk_00 = 0;
    actor->handler = spawn_effect_after_timeout;
    actor->timer = 21;
}
