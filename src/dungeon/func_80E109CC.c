#include "common.h"

typedef struct S_801741CC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x4];
    u16 unk_AC;
} S_801741CC_0;   /* arg0 in func_801741CC */

typedef struct S_801741CC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801741CC_1;   /* arg2 in func_801741CC */

typedef struct S_801741CC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801741CC_2;   /* base in func_801741CC */

typedef struct S_801741CC_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801741CC_3;   /* arg3 in func_801741CC */

typedef struct S_801741CC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801741CC_4;   /* global in func_801741CC */

typedef struct S_801741CC_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801741CC_5;   /* D_800814A8 in func_801741CC */



extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174520(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171094;
extern u8 D_80176470[];
extern u8 D_80176478[];

void func_801741CC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;

    state = ((S_801741CC_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    {
        s32 *base;
        u8 *table;

        if (!(((S_801741CC_1 *)arg2)->unk_14 & 0xE000)) {
            goto done;
        }

        base = &D_80083460;
        ((S_801741CC_2 *)base)->unk_0A--;
        table = D_80176470;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_801741CC_3 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u8 *global;
        u32 flags;

        if (((S_801741CC_3 *)arg3)->unk_25 != 0) {
            s32 *base;

            (*(void * *)((u8 *)arg2 + 0x2C)) = D_80176478;
            func_80047784(arg2,
                D_80176478[((D_80083228 + ((S_801741CC_3 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801741CC_3 *)arg3)->unk_1C |= 0x40000;
            base = &D_80083460;
            ((S_801741CC_2 *)base)->unk_0A++;
            goto increment_state;
        }

        global = (u8 *)&D_80083460;
        if (((S_801741CC_4 *)global)->unk_02 & 0x1000) {
            goto done;
        }

        if (((S_801741CC_3 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }

        flags = ((S_801741CC_3 *)arg3)->unk_1C;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (flags & 0x80000) {
            u16 old_value;
            u16 amount;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = ((S_801741CC_0 *)arg0)->unk_92;
            amount = ((S_801741CC_0 *)arg0)->unk_A6;
            ((S_801741CC_0 *)arg0)->unk_A6 = 0;
            ((S_801741CC_0 *)arg0)->unk_AC = 0;
            ((S_801741CC_0 *)arg0)->unk_92 = old_value - amount;
            func_80174520(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (((S_801741CC_3 *)arg3)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)((S_801741CC_5 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (((S_801741CC_3 *)arg3)->unk_25 == 0) {
            goto done;
        }

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80176478;
        func_80047784(arg2,
            D_80176478[((D_80083228 + ((S_801741CC_3 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801741CC_3 *)arg3)->unk_1C |= 0x40000;
        ((S_801741CC_4 *)global)->unk_0A++;
    }

increment_state:
    ((S_801741CC_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (((S_801741CC_1 *)arg2)->unk_14 & 0xE000) {
        s32 *base;

        base = &D_80083460;
        ((S_801741CC_2 *)base)->unk_0A--;
        ((S_801741CC_3 *)arg3)->unk_1C &= ~8;
        ((S_801741CC_0 *)arg0)->unk_8C = &D_80171094;
    }

done:
    return;
}
