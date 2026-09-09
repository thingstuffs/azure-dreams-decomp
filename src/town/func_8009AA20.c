#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 unkA;
} Func8009AA20Arg0;

typedef struct {
    u16 pad;
    u16 unk2;
} Func8009AA20Arg1;

extern void func_80098D60(Func8009AA20Arg0 *arg0, Func8009AA20Arg1 *arg1, s32 arg2);

/* Decrement the countdown, invoking its handler when exhausted or advancing the cursor by four. */
void func_80098180(Func8009AA20Arg0 *countdown_state, Func8009AA20Arg1 *cursor_state, s32 context_value) {
    u16 remaining_count;

    remaining_count = countdown_state->unkA - 1;
    countdown_state->unkA = remaining_count;
    if ((s16)remaining_count < 0) {
        func_80098D60(countdown_state, cursor_state, context_value);
        return;
    }
    cursor_state->unk2 += 4;
}
