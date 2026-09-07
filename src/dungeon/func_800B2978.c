#include "common.h"

typedef struct S_800B80D8_0 {
    u8 pad_00[0xA2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u16 unk_A4;
    u8 pad_A6[0xA];
    s16 unk_B0;
    s16 unk_B2;
} S_800B80D8_0;   /* arg0 in func_800B80D8 */

typedef struct S_800B80D8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800B80D8_1;   /* arg2 in func_800B80D8 */

typedef struct S_800B80D8_2 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B80D8_2;   /* arg1 in func_800B80D8 */



extern void func_800A7A7C(s32, s32, s32, void *, void *);
extern s32 D_8006E240;
extern s32 D_800814A0;

void func_800B80D8(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s32 velocity;
    u16 counter;
    u16 pos;

    state = ((S_800B80D8_0 *)arg0)->unk_A2.s;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto exit;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto exit;

state_zero:
    if (!(((S_800B80D8_1 *)arg2)->unk_14 & 0x8000)) {
        goto zero_continue;
    }
    ((S_800B80D8_0 *)arg0)->unk_A2.u = 2;
    goto exit;

zero_continue:
    ((S_800B80D8_0 *)arg0)->unk_A4 = 12;
    ((S_800B80D8_0 *)arg0)->unk_A2.u++;
state_one:
    velocity = ((S_800B80D8_2 *)arg1)->unk_14 + 0x30000;
    ((S_800B80D8_2 *)arg1)->unk_14 = velocity;
    ((S_800B80D8_2 *)arg1)->unk_08.at00.v += velocity;
    pos = ((S_800B80D8_1 *)arg2)->unk_1C;
    if (pos < 0x1000) {
        ((S_800B80D8_1 *)arg2)->unk_1C = pos + 0x50;
        ((S_800B80D8_1 *)arg2)->unk_1E += 0x50;
    }
    counter = ((S_800B80D8_0 *)arg0)->unk_A4 - 1;
    ((S_800B80D8_0 *)arg0)->unk_A4 = counter;
    if ((counter << 16) != 0) {
        goto exit;
    }
    ((S_800B80D8_2 *)arg1)->unk_14 = 0;
    ((S_800B80D8_0 *)arg0)->unk_A2.u++;
    goto exit;

state_two:
    func_800A7A7C(((S_800B80D8_0 *)arg0)->unk_B0,
                  ((S_800B80D8_0 *)arg0)->unk_B2,
                  (s16)(((S_800B80D8_2 *)arg1)->unk_08.at02.v - 0x20),
                  &D_8006E240,
                  (u8 *)arg0 + 0x98);
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

exit:
    return;
}

/* MECHANISM: true-space local jumps are C returns to one shared epilogue.
   A 0x20 frame holds only arg0 in s0 across the one real five-argument call;
   arg1 naturally occupies a3, and phase-one is a labeled fallthrough join. */
