#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched townInitializeObjectEntries body. */
extern void townInitializeObjectEntries(void *state, s8 *output, s32 *entries);
#include "shared/object_index_slots.h"

extern s32 D_800D6A98[];
extern u8 D_800C3B7C[];


void initialize_actor_twenty_eight_tick_countdown(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    townInitializeObjectEntries(actor, output, D_800D6A98);
    D_80082660[actor->unk_60].unk_00 = 0;
    actor->unk_54 = D_800C3B7C;
    actor->unk_6C.as_s16 = 28;
}
