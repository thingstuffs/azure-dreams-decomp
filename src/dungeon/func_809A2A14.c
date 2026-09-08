#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801744F8(void) __attribute__((noreturn));
extern void func_80174574(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801710EC;
extern u8 D_80175EA0[];
extern u8 D_80175EC0[];


typedef struct S_80174214_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174214_0;   /* arg0 in func_80174214 */


typedef struct S_80174214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174214_2;   /* base in func_80174214 */


typedef struct S_80174214_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174214_4;   /* global in func_80174214 */


void func_80174214(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;

    state = ((S_80174214_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

at_least_two:
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    {
        s32 *base;
        u8 *table;

        if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000)) {
            goto done;
        }

        base = &D_80083460;
        ((S_80174214_2 *)base)->unk_0A--;
        table = D_80175EA0;
        if (((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv != table) {
            (*(void * *)((u8 *)arg2 + (0x2C))) = table;
            func_80047784(arg2,
                table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            func_801744F8();
        }
        goto increment_state;
    }

state_one:
    {
        u8 *global;
        u32 flags;

        if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v != 0) {
            s32 *base;

            (*(void * *)((u8 *)arg2 + (0x2C))) = D_80175EC0;
            func_80047784(arg2,
                D_80175EC0[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
            base = &D_80083460;
            ((S_80174214_2 *)base)->unk_0A++;
            func_801744F8();
        }

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        global = (u8 *)&D_80083460;
        if (((S_80174214_4 *)global)->unk_02 & 0x1000) {
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
        {
        void *call_arg0 = arg0;

        if (flags & 0x100) {
            func_800AA258(call_arg0, arg1, arg2, arg3);
            return;
        }

           /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (flags & 0x80000) {
            u16 old_value;
            u16 amount;

            func_800AA888(call_arg0, arg1, arg2, arg3);
            old_value = ((S_80174214_0 *)arg0)->unk_92;
            amount = ((S_80174214_0 *)arg0)->unk_A2;
            ((S_80174214_0 *)arg0)->unk_A2 = 0;
            ((S_80174214_0 *)arg0)->unk_9E = 0;
            ((S_80174214_0 *)arg0)->unk_92 = old_value - amount;
            func_80174574(arg0, arg1, arg2, arg3);
            return;
        }
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

        (*(void * *)((u8 *)arg2 + (0x2C))) = D_80175EC0;
        func_80047784(arg2,
            D_80175EC0[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
        ((S_80174214_4 *)global)->unk_0A++;
    }

increment_state:
    ((S_80174214_0 *)arg0)->unk_9B++;
    return;

state_two:
    if (((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000) {
        s32 *base;

        base = &D_80083460;
        ((S_80174214_2 *)base)->unk_0A--;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~8;
        ((S_80174214_0 *)arg0)->unk_8C = &D_801710EC;
    }

done:
    return;
}

/* MECHANISM: Four live argument bases plus the held D_80083460 base produce the retail 0x28 frame.
   The callback-equality edge, state continuations, and exact callee ABIs restore the 216-word CFG.
   Scheduler barriers and a guarded $a0 carrier close the three remaining delay-slot rotations. */
