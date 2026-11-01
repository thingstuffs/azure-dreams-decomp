#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "town/system/object_hooks.h"
#include "shared/town_object.h"

#include "shared/object_index_slots.h"

extern s32 D_800D6A98[];


void initialize_actor_twenty_eight_tick_countdown(TownObjectRecord *actor, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(actor, output, D_800D6A98);
    object_index_slots[actor->slot].unk_00 = 0;
    actor->handler = person_countdown_update_address;
    actor->timer.as_s16 = 28;
}
