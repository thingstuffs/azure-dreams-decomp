#include "shared/sound_state.h"
#include "common.h"




/* Activates and clears pending state, rearms the counter and timer, and clears status flags. */
void func_80054C58(void) {
    SoundPlaybackState *state = &D_800847D0;
    u32 pending_word_a = state->unk_10;
    u32 pending_word_b = state->unk_14;
    u8 pending_byte_a = ((u8)state->unk_31);
    u8 pending_byte_b = ((u8)state->unk_33);

    state->unk_10 = 0;
    state->unk_14 = 0;
    ((u8)state->unk_31) = 0;
    ((u8)state->unk_33) = 0;

    D_80084858.unk_0C = 3;
    D_80084858.unk_10 = 0x80;

    state->unk_08 = pending_word_a;
    state->unk_0C = pending_word_b;
    ((u8)state->unk_30) = pending_byte_a;
    ((u8)state->unk_32) = pending_byte_b;

    state->flags00 &= ~0x400;
    state->flags00 &= ~0x4000;
    state->flags04 &= ~0x200;
}
