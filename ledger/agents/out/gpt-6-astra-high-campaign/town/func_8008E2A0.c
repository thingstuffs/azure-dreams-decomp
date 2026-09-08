#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008BA00_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    u8 pad_66[0x2];
    M2C_UNK (*unk_68)();
    M2C_UNK (*unk_6C)();
} S_8008BA00_0;   /* arg0 in func_8008BA00 */


/* Decrement the countdown and activate the next callback when it becomes negative. */
void func_8008BA00(S_8008BA00_0 *state) {
    M2C_UNK (*next_callback)();
    u16 countdown;

    countdown = state->unk_64 - 1;
    state->unk_64 = countdown;
    if ((s16) countdown < 0) {
        next_callback = state->unk_6C;
        state->unk_68 = next_callback;
        next_callback();
    }
}
