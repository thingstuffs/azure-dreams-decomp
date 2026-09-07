#include "common.h"

typedef struct S_80173514_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173514_0;   /* arg0 in func_80173514 */

typedef struct S_80173514_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80173514_1;   /* arg2 in func_80173514 */

typedef struct S_80173514_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173514_2;   /* arg1 in func_80173514 */

typedef struct S_80173514_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80173514_3;   /* arg3 in func_80173514 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8017373C() __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170870[20];
extern s32 D_80171CE8;
extern u8 D_80174EE0[];

void func_80173514(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = ((S_80173514_0 *)arg0)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170870)[state]);

L0:
    {
    register void *call_a0 ASM_REG("$4") = arg3;   /* MATCH pin: retail basic-block layout depends on it */
    if (((S_80173514_1 *)arg2)->unk_14 & 0x8000) {
        ((S_80173514_0 *)arg0)->unk_9B = 4;
        ((S_80173514_1 *)arg2)->unk_14 |= 0x6000;
        func_8017373C(call_a0, arg2);
        return;
    }
    ((S_80173514_2 *)arg1)->unk_14 = 0;
    ((S_80173514_2 *)arg1)->unk_10 = 0;
    ((S_80173514_2 *)arg1)->unk_0C = 0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174EE0;
    func_80047784(arg2,
        D_80174EE0[((D_80083228 + ((S_80173514_3 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80173514_0 *)arg0)->unk_96.s = 0;
    ((S_80173514_0 *)arg0)->unk_9B++;
    return;
    }

L1:
    if ((s16)++((S_80173514_0 *)arg0)->unk_96.s == 5) {
        ((S_80173514_0 *)arg0)->unk_96.s = 0;
        ((S_80173514_0 *)arg0)->unk_9B++;
        ((S_80173514_1 *)arg2)->unk_14 |= 0x0800;
        return;
    }
    return;

L2:
    if ((s16)++((S_80173514_0 *)arg0)->unk_96.s == 6 ||
        (((S_80173514_1 *)arg2)->unk_14 & 0xE000)) {
        ((S_80173514_0 *)arg0)->unk_96.s = 0;
        ((S_80173514_0 *)arg0)->unk_9B++;
        ((S_80173514_1 *)arg2)->unk_14 &= 0xF7FF;
        func_800A56E0(0x804);
        return;
    }
    return;

L3:
    if ((s16)++((S_80173514_0 *)arg0)->unk_96.s == 5 ||
        (((S_80173514_1 *)arg2)->unk_14 & 0xE000)) {
        ((S_80173514_1 *)arg2)->unk_14 |= 0x0800;
    }
    if (((S_80173514_0 *)arg0)->unk_96.u == 12 ||
        (((S_80173514_1 *)arg2)->unk_14 & 0xE000)) {
        ((S_80173514_0 *)arg0)->unk_96.s = 0;
        ((S_80173514_0 *)arg0)->unk_9B++;
        ((S_80173514_1 *)arg2)->unk_14 &= 0xF7FF;
    }
    if (((S_80173514_0 *)arg0)->unk_96.u == 1 ||
        (((S_80173514_1 *)arg2)->unk_14 & 0xE000)) {
        func_8009C12C(arg3, arg2, ((S_80173514_3 *)arg3)->unk_2A, 1);
        return;
    }
    return;

L4:
    if (((S_80173514_1 *)arg2)->unk_14 & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_80173514_0 *)arg0)->unk_8C = &D_80171CE8;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((S_80173514_3 *)arg3)->unk_46 &= 0x7FFF;
    }
}
