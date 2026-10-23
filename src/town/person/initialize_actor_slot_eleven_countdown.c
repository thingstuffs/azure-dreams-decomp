#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched initialize_object_entries body. */
extern void initialize_object_entries(void *state, s8 *output, s32 *entries);

extern s32 D_800D64C8[];
extern u8 D_800C9F58[];
extern s8 D_800826B8;


/* Initializes entries from D_800D64C8, clears D_800826B8, and installs D_800C9F58 with count four. */
void initialize_actor_slot_eleven_countdown(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    initialize_object_entries(actor, output, D_800D64C8);
    D_800826B8 = 0;
    actor->unk_54 = D_800C9F58;
    actor->unk_6C.as_s16 = 4;
}
