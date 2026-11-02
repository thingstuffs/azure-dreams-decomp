#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person.h"
extern s32 D_800C5B48[];
extern s32 D_800D54CC[];

/* Initialize the actor state, clear its entry flag, and start a 16-tick callback countdown. */
void initialize_actor_with_16_tick_callback(TownObjectRecord *actor, s32 unused, void *state_context) {
    initialize_object_entries(actor, state_context, D_800D54CC);
    object_index_slots[actor->slot].unk_00 = 0;
    actor->timer.as_s16 = 0x10;
    actor->handler = D_800C5B48;
}
