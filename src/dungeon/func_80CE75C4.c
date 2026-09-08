#include "common.h"

typedef struct S_80170DC4_0_pre {
    u16 unk_00;
} S_80170DC4_0_pre;   /* the 0x2 bytes before arg0 in func_80170DC4, addressed as arg0[-1] */

typedef struct S_80170DC4_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
} S_80170DC4_0;   /* arg0 in func_80170DC4 */

typedef struct S_80170DC4_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80170DC4_1;   /* arg2 in func_80170DC4 */


typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;


extern GlobalFlags D_800814A0;

/* Decrement the countdown, update three scaled output components, and flag completion. */
void func_80170DC4(void *countdownState, s32 unused, S_80170DC4_1 *output) {
    s32 scaledRemaining;
    u16 remainingCount;

    remainingCount = ((S_80170DC4_0 *)countdownState)->unk_96 - 1;
    scaledRemaining = (s32) ((s32) (remainingCount << 16) >> 9) / ((S_80170DC4_0 *)countdownState)->unk_9E;
    ((S_80170DC4_0 *)countdownState)->unk_96 = remainingCount;
    output->unk_0C = (s8) scaledRemaining;
    output->unk_0E = (s8) scaledRemaining;
    output->unk_0D = (s8) scaledRemaining;
    if ((s16) ((S_80170DC4_0 *)countdownState)->unk_96 <= 0) {
        ((S_80170DC4_0_pre *)countdownState)[-1].unk_00 = ((S_80170DC4_0_pre *)countdownState)[-1].unk_00 | 0x8000;
        D_800814A0.value = D_800814A0.value | 0x8000;
    }
}
