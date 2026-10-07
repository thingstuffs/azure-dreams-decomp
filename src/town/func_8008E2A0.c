#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008BA00_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    u8 pad_66[0x2];
    s32 (*unk_68)(struct S_8008BA00_0 *);
    s32 (*unk_6C)(struct S_8008BA00_0 *);
} S_8008BA00_0;   /* arg0 in func_8008BA00 */


/* Decrement the countdown and activate the next callback when it becomes negative. */
void func_8008BA00(S_8008BA00_0 *state) {
    s32 (*next_callback)(S_8008BA00_0 *);
    u16 countdown;

    countdown = state->unk_64 - 1;
    state->unk_64 = countdown;
    if ((s16) countdown < 0) {
        next_callback = state->unk_6C;
        state->unk_68 = next_callback;
        next_callback(state);
    }
}
