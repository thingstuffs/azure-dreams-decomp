#include "common.h"

typedef struct S_80172D04_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172D04_0;   /* arg0 in func_80172D04 */

typedef struct S_80172D04_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172D04_1;   /* arg1 in func_80172D04 */

typedef struct S_80172D04_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x41];
    u16 unk_6A;
} S_80172D04_2;   /* arg3 in func_80172D04 */

typedef struct S_80172D04_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172D04_3;   /* arg2 in func_80172D04 */



extern void func_800A2B04(void *, u8, u8);
extern s32 func_800A6D30(void);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_8017516C(void *, void *, void *, void *);
extern void func_80176480(void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170EE4[];
extern u8 D_80176640[];

void func_80172D04(S_80172D04_0 *arg0, S_80172D04_1 *arg1, S_80172D04_3 *arg2, void *arg3)
{
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 random;
    s32 one;

    state = arg0->unk_9B;
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    func_80176480(arg1, arg2);
    func_800AD4D0(arg3);
    arg1->unk_0C =
        -*(s16 *)((u8 *)&D_8006CCD8 +
            ((((S_80172D04_2 *)arg3)->unk_6A >> 8) & 0xE)) << 15;
    arg1->unk_10 =
        -*(s16 *)((u8 *)&D_8006CCE8 +
            ((((S_80172D04_2 *)arg3)->unk_6A >> 8) & 0xE)) << 15;
    arg0->unk_9B++;

    if (((S_80172D04_2 *)arg3)->unk_28 == 0) {
        goto reset_motion;
    }
    random = func_800A6D30() & 3;
    if (arg2->unk_14 & 0x8000) {
        if (random == 0) {
            func_8017516C(arg0, arg1, arg2, arg3);
        }
        arg0->unk_A8.s = -1;
        arg0->unk_96.s = 0;
        arg0->unk_9B = 2;
        return;
    }
    timer = -1;
    if (((S_80172D04_2 *)arg3)->unk_1C & 0x228) {
        timer = 8;
    }
    arg0->unk_96.s = timer;
    if (random != 0) {
        arg0->unk_A8.s = -1;
        goto state_1;
    }
    arg0->unk_A8.u = one;

state_1:
    value = arg1->unk_0C;
    adjusted = value;
    if (value < 0) {
        adjusted = value + 3;
    }
    value2 = arg1->unk_10;
    arg1->unk_0C = value - (adjusted >> 2);

    adjusted = value2;
    if (value2 < 0) {
        adjusted = value2 + 3;
    }
    arg1->unk_10 = value2 - (adjusted >> 2);

    timer = arg0->unk_A8.u - 1;
    arg0->unk_A8.u = timer;
    if ((timer << 16) == 0) {
        func_8017516C(arg0, arg1, arg2, arg3);
    }

    if (arg0->unk_96.s > 0) {
        arg0->unk_96.u = arg0->unk_96.u - 1;
    } else if (arg2->unk_14 & 0x6000) {
        arg0->unk_96.s = 0;
    }

    if (arg0->unk_96.s != 0) {
        return;
    }
    if (((S_80172D04_2 *)arg3)->unk_28 != 0) {
        goto increment_state;
    }

reset_motion:
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800AAA54(arg0, arg1, arg2, D_80176640);
    return;

increment_state:
    arg0->unk_96.s = 8;
    arg0->unk_9B++;
    return;

state_2:
    timer = arg0->unk_96.s;
    if (timer != 0) {
        s32 sub, m;
        m = arg2->unk_24;
        m <<= 6;
        sub = arg1->unk_02 - 0x20;
        arg1->unk_0C = ((m - sub) << 15) / timer;
        sub = arg1->unk_06 - 0x20;
        arg1->unk_10 =
            (((arg2->unk_25 << 6) - sub) << 15) /
            arg0->unk_96.s;
    }

    timer = arg0->unk_A8.u - 1;
    arg0->unk_A8.u = timer;
    if ((timer << 16) == 0) {
        func_8017516C(arg0, arg1, arg2, arg3);
    }

    timer = arg0->unk_96.u - 1;
    arg0->unk_96.s = timer;
    if ((timer << 16) > 0) {
        return;
    }

    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24,
        arg2->unk_25);
    {
        s32 *global;

        global = &D_80083460;
        value = *(s32 *)((u8 *)global + 0x10);
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
        }
    }
    arg0->unk_8C = D_80170EE4;
}
