#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017409C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_8017409C_0;   /* arg0 in func_8017409C */


typedef struct S_8017409C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017409C_2;   /* base in func_8017409C */


typedef struct S_8017409C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017409C_4;   /* global in func_8017409C */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

void func_8017409C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;

    state = ((S_8017409C_0 *)arg0)->unk_9B;
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

        if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000)) {
            goto done;
        }

        base = &D_80083460;
        ((S_8017409C_2 *)base)->unk_0A--;
        table = D_80174684;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u8 *global;
        u32 flags;

        if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v != 0) {
            s32 *base;

            (*(void * *)((u8 *)arg2 + 0x2C)) = D_8017468C;
            func_80047784(arg2,
                D_8017468C[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
            base = &D_80083460;
            ((S_8017409C_2 *)base)->unk_0A++;
            goto increment_state;
        }

        global = (u8 *)&D_80083460;
        if (((S_8017409C_4 *)global)->unk_02 & 0x1000) {
            goto done;
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }

        flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (flags & 0x80000) {
            u16 old_value;
            u16 amount;
            u32 saved;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = ((S_8017409C_0 *)arg0)->unk_92;
            amount = ((S_8017409C_0 *)arg0)->unk_A4.at02.v;
            saved = ((S_8017409C_0 *)arg0)->unk_A4.at00.v;
            ((S_8017409C_0 *)arg0)->unk_A4.at02.v = 0;
            ((S_8017409C_0 *)arg0)->unk_B8 = 0;
            ((S_8017409C_0 *)arg0)->unk_AC = 0;
            ((S_8017409C_0 *)arg0)->unk_B0 = 0;
            ((S_8017409C_0 *)arg0)->unk_92 = old_value - amount;
            ((S_8017409C_0 *)arg0)->unk_A8 = saved;
            func_801743F0(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
            goto done;
        }

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_8017468C;
        func_80047784(arg2,
            D_8017468C[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        (*(u32 *)((u8 *)arg3 + 0x1C)) |= 0x40000;
        ((S_8017409C_4 *)global)->unk_0A++;
    }

increment_state:
    ((S_8017409C_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000) {
        s32 *base;

        base = &D_80083460;
        ((S_8017409C_2 *)base)->unk_0A--;
        ((S_8017409C_0 *)arg0)->unk_8C = &D_801719DC;
    }

done:
    return;
}
