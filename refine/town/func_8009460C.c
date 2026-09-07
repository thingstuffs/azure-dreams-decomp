#include "common.h"

typedef struct S_80091D6C_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x28];
    s16 unk_34;
} S_80091D6C_0;   /* arg0 in func_80091D6C */

typedef struct S_80091D6C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80091D6C_1;   /* arg1 in func_80091D6C */



extern s32 func_80094220(void *, void *, s32);
extern void func_80094984(void *, void *, s32);
extern void func_80095C80(void *);
extern s32 D_800D00E8;
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

/* Updates countdown-driven motion and invokes callbacks at selected ticks. */
void func_80091D6C(S_80091D6C_0 *state, S_80091D6C_1 *motion, s32 callback_arg) {
    s16 ticks_left;
    s32 target_position;

    func_80095C80(motion);
    if (state->unk_0A >= 15) {
        target_position = (s32)((u32)(state->unk_34 +
                   D_800D0454[21 - state->unk_0A]) << 16);
        goto selector_join;
    } else {
        target_position = (s32)((u32)state->unk_34 << 16);
    }

selector_join:
    if (state->unk_0A == 19)
        func_80094984(&D_800D00E8, state, callback_arg);
    if (state->unk_0A == 15)
        func_80094984(&D_800D00F0, state, callback_arg);
    if (state->unk_0A == 12)
        func_80094984(&D_800D00F8, state, callback_arg);
    ticks_left = (u16)state->unk_0A - 1;
    state->unk_0A = ticks_left;
    if ((s32)((u32)(u16)ticks_left << 16) <= 0) {
        motion->unk_0C = 0;
        motion->unk_10 = 0;
        motion->unk_14 = 0;
        func_80094220(state, motion, callback_arg);
        return;
    }
    motion->unk_14 = target_position - motion->unk_08;
}
