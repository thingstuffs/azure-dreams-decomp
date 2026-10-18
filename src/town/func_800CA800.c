#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched initialize_object_entries body. */
extern void initialize_object_entries(void *state, s8 *output, s32 *entries);

extern s32 D_800D5FE8[];
extern u8 D_800C7CF0[];
extern s8 D_80082680;


void initialize_actor_slot_four_countdown(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    initialize_object_entries(actor, output, D_800D5FE8);
    D_80082680 = 0;
    actor->unk_54 = D_800C7CF0;
    actor->unk_6C.as_s16 = 16;
}
