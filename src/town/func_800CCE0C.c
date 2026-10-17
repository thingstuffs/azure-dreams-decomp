#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched townInitializeObjectEntries body. */
extern void townInitializeObjectEntries(void *state, s8 *output, s32 *entries);

extern s32 D_800D64C8[];
extern u8 D_800C9F58[];
extern s8 D_800826B8;


void initialize_actor_slot_eleven_countdown(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    townInitializeObjectEntries(actor, output, D_800D64C8);
    D_800826B8 = 0;
    actor->unk_54 = D_800C9F58;
    actor->unk_6C.as_s16 = 4;
}
