#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person/state_updates.h"

/* Pointer arguments follow the matched initialize_object_entries body. */
extern void initialize_object_entries(void *state, s8 *output, s32 *entries);

extern s32 D_800D64DC[];
extern u8 D_800CA020[];


/* Initializes entries from D_800D64DC and installs D_800CA020 as the actor handler. */
void initialize_actor_primary_handler(Rec_func_80094268_arg0 *actor, void *unused, void *output) {
    initialize_object_entries(actor, output, D_800D64DC);
    actor->unk_54 = D_800CA020;
}
