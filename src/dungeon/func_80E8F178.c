#include "common.h"

typedef struct S_80174978_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    s16 unk_AA;
} S_80174978_0;   /* arg0 in func_80174978 */

typedef struct S_80174978_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80174978_1;   /* arg2 in func_80174978 */

typedef struct S_80174978_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80174978_2;   /* arg1 in func_80174978 */



extern void func_800A7A7C(s16, s16, s16, s32, void *);
extern s32 D_800814A0;

void func_80174978(void *arg0, void *arg1, void *arg2) {
    s32 state;
    s32 delta;
    s32 value;
    register s32 sum ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 timer;
    u16 next;

    state = ((S_80174978_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (((S_80174978_1 *)arg2)->unk_14 & 0x8000) {
        ((S_80174978_0 *)arg0)->unk_9B = 2;
        goto done;
    }
    ((S_80174978_0 *)arg0)->unk_96 = 12;
    ((S_80174978_0 *)arg0)->unk_9B = ((S_80174978_0 *)arg0)->unk_9B + 1;

state_one: {
    s32 left;
    s32 right;

    left = ((S_80174978_0 *)arg0)->unk_A8 << 6;
    right = ((S_80174978_2 *)arg1)->unk_02 - 0x20;
    ((S_80174978_2 *)arg1)->unk_02 = (u16)((S_80174978_2 *)arg1)->unk_02 +
        ((left - right) >> 1);
}
    delta = ((S_80174978_0 *)arg0)->unk_AA;
    value = ((S_80174978_2 *)arg1)->unk_14 + 0x30000;
    sum = ((S_80174978_2 *)arg1)->unk_08.at00.v + value;
    ((S_80174978_2 *)arg1)->unk_14 = value;
    value = ((S_80174978_2 *)arg1)->unk_06;
    delta <<= 6;
    ((S_80174978_2 *)arg1)->unk_08.at00.v = sum;
    value -= 0x20;
    delta -= value;
    delta >>= 1;
    ((S_80174978_2 *)arg1)->unk_06 = (u16)((S_80174978_2 *)arg1)->unk_06 + delta;
    if (((S_80174978_1 *)arg2)->unk_1C < 0x1000U) {
        next = ((S_80174978_1 *)arg2)->unk_1E + 0x50;
        ((S_80174978_1 *)arg2)->unk_1E = next;
        ((S_80174978_1 *)arg2)->unk_1C = next;
    }
    timer = ((S_80174978_0 *)arg0)->unk_96 - 1;
    ((S_80174978_0 *)arg0)->unk_96 = timer;
    if ((timer << 16) != 0) {
        goto done;
    }
    ((S_80174978_2 *)arg1)->unk_14 = 0;
    ((S_80174978_0 *)arg0)->unk_9B = ((S_80174978_0 *)arg0)->unk_9B + 1;
    goto done;

state_two:
    func_800A7A7C(((S_80174978_0 *)arg0)->unk_A8,
                  ((S_80174978_0 *)arg0)->unk_AA,
                  (s16)(((S_80174978_2 *)arg1)->unk_08.at02.v - 0x20),
                  ((S_80174978_1 *)arg2)->unk_08, arg0 + 0x48);
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
