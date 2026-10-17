#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched townInitializeObjectEntries body. */
extern void townInitializeObjectEntries(void *state, s8 *output, s32 *entries);

extern s32 D_800D64DC[];
extern u8 D_800CA020[];


void initialize_actor_primary_handler(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    townInitializeObjectEntries(actor, output, D_800D64DC);
    actor->unk_54 = D_800CA020;
}
