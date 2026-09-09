#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800CE2D4_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x16];
    s16 unk_84;
    s16 unk_86;
} S_800CE2D4_0;   /* arg0 in func_800CE2D4 */

typedef struct S_800CE2D4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CE2D4_1;   /* arg1 in func_800CE2D4 */


M2C_UNK func_800C4174(S_800CE2D4_0 *, S_800CE2D4_1 *, M2C_UNK);
/* Decrement the countdown and ease the current values toward their targets. */
void func_800CE2D4(S_800CE2D4_0 *state, S_800CE2D4_1 *current, M2C_UNK context) {
    u16 ticks_left;
    u32 target_delta;

    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800C4174(state, current, context);
    }
    current->unk_02 = (s16) ((u16) current->unk_02 + ((s32) (state->unk_84 - current->unk_02) / 2));
    target_delta = state->unk_86 - current->unk_06;
    current->unk_0A = (s16) ((u16) current->unk_0A + ((s32) (0 - current->unk_0A) / 2));
    current->unk_06 = (s16) ((u16) current->unk_06 + ((s32) (target_delta + (target_delta >> 0x1F)) >> 1));
}
