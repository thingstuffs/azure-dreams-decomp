#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched initialize_object_entries body. */
extern void initialize_object_entries(void *state, s8 *output, s32 *entries);
#include "shared/object_index_slots.h"

extern s32 D_800D6A98[];
extern u8 person_countdown_update_address[];


void initialize_actor_twenty_eight_tick_countdown(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    initialize_object_entries(actor, output, D_800D6A98);
    object_index_slots[actor->unk_60].unk_00 = 0;
    actor->unk_54 = person_countdown_update_address;
    actor->unk_6C.as_s16 = 28;
}
