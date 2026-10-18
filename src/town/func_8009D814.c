#include "common.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void update_player_global_state(void *entity, s32 unused_1, s32 unused_2);
extern u8 D_800D0078[];
extern void *D_8009AFF4[];

typedef struct {
    s32 unk0;
    void **unk4;
    u16 unk8;
    u16 unkA;
} Struct8009D814;

/* Decrement the countdown, switch the state's table on expiry, and update the state. */
void advance_player_state_table(Struct8009D814 *state, s32 update_arg, s32 shared_arg) {
    s16 countdown;

    countdown = state->unkA - 1;
    state->unkA = countdown;
    if (countdown <= 0) {
        call_the_handler_selects_nonzero_entry(D_800D0078, state, shared_arg);
        state->unk4 = D_8009AFF4;
    }
    update_player_global_state(state, update_arg, shared_arg);
}
