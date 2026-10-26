#include "common.h"
#include "engine/window.h"

#include "common.h"
#include "slus/data.h"

typedef struct S_80036484_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x3];
    s8 unk_51;
    u8 pad_52[0x12];
    u16 unk_64;
    u8 pad_66[0x2];
    s32 * unk_68;
} S_80036484_0;   /* arg0 in runtime_decrement_countdown_and_reset */

/* Decrements the countdown and resets state before switching handlers when it expires. */
void runtime_decrement_countdown_and_reset(S_80036484_0 *state) {
    u16 countdown;

    countdown = state->unk_64 - 1;
    state->unk_64 = countdown;
    if ((countdown << 0x10) <= 0) {
        state->unk_4D = 0xFF;
        state->unk_51 = 0;
        state->unk_68 = &runtime_mark_state_when_flag_51_set;
    }
}
