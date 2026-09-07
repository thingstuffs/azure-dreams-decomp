#include "common.h"

typedef struct S_80173CD4_0 {
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
} S_80173CD4_0;   /* arg0 in func_80173CD4 */

typedef struct S_80173CD4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173CD4_1;   /* arg2 in func_80173CD4 */

typedef struct S_80173CD4_2 {
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
} S_80173CD4_2;   /* arg3 in func_80173CD4 */

typedef struct S_80173CD4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173CD4_3;   /* base in func_80173CD4 */

typedef struct S_80173CD4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173CD4_4;   /* global in func_80173CD4 */

typedef struct S_80173CD4_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173CD4_5;   /* D_800814A8 in func_80173CD4 */

typedef struct S_80173CD4_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173CD4_6;   /* origin in func_80173CD4 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

void func_80173CD4(void *in0, void *in1, void *in2, void *in3)
{
    s32 state;
    void *arg0 = in0;
    register void *arg1 ASM_REG("$19") = in1;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *arg2 ASM_REG("$17") = in2;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *arg3;
    register u8 *global ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    state = ((S_80173CD4_0 *)arg0)->unk_9B;
    arg3 = in3;
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
        u8 *base;
        u8 *table;
        if (!(((S_80173CD4_1 *)arg2)->unk_14 & 0xE000)) {
            goto done;
        }
        table = D_80174684;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173CD4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        base = (u8 *)&D_80083460;
        ((S_80173CD4_3 *)base)->unk_0A--;
        goto increment_state;
    }

state_one:
    {
        register u32 global_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        u32 flags;

        if ((func_80042900(arg3, 1) << 16) == 0) {
            goto animate;
        }

        global_page = 0x80080000;
        ASM_KEEP(global_page);   /* MATCH pin: load-bearing for the whole function shape */
        global = (u8 *)(global_page + 0x3460);
        if (((S_80173CD4_4 *)global)->unk_02 & 0x1000) {
            goto done;
        }

        if (((S_80173CD4_2 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if (((S_80173CD4_2 *)arg3)->unk_25 == 0) {
            if (((S_80173CD4_4 *)global)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }

        flags = ((S_80173CD4_2 *)arg3)->unk_1C;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (flags & 0x80000) {
            u16 old_value;
            u16 amount;
            u32 saved;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = ((S_80173CD4_0 *)arg0)->unk_92;
            amount = ((S_80173CD4_0 *)arg0)->unk_A4.at02.v;
            saved = ((S_80173CD4_0 *)arg0)->unk_A4.at00.v;
            ((S_80173CD4_0 *)arg0)->unk_A4.at02.v = 0;
            ((S_80173CD4_0 *)arg0)->unk_B8 = 0;
            ((S_80173CD4_0 *)arg0)->unk_AC = 0;
            ((S_80173CD4_0 *)arg0)->unk_B0 = 0;
            ((S_80173CD4_0 *)arg0)->unk_92 = old_value - amount;
            ((S_80173CD4_0 *)arg0)->unk_A8 = saved;
            func_801743F0(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (((S_80173CD4_2 *)arg3)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)((S_80173CD4_5 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = ((S_80173CD4_1 *)arg2)->unk_26;
            if ((((coordinate == ((S_80173CD4_6 *)origin)->unk_26) &&
                    (coordinate >= 0)) ||
                    (func_8009FD40(origin, arg2) < 2)) &&
                    !(func_800A6D30() & 7)) {
                func_80042B68(arg3, 1);
            }
        }

        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto done;
        }
    }

animate:
    {
        u8 *table;

        table = D_8017468C;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173CD4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80173CD4_2 *)arg3)->unk_1C |= 0x40000;
        if (((S_80173CD4_1 *)arg2)->unk_14 & 0x8000) {
            goto set_pointer;
        }

        {
            register u8 *base ASM_REG("$2") = (u8 *)&D_80083460;   /* MATCH pin: load-bearing for the whole function shape */
            ((S_80173CD4_3 *)base)->unk_0A++;
        }
    }

increment_state:
    ((S_80173CD4_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (((S_80173CD4_1 *)arg2)->unk_14 & 0xE000) {
        register u8 *base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        base = (u8 *)&D_80083460;
        ((S_80173CD4_3 *)base)->unk_0A--;
        goto set_pointer;
    }
    goto done;

set_pointer:
    ((S_80173CD4_0 *)arg0)->unk_8C = &D_801719DC;

done:
    return;
}

/* MECHANISM: Delayed a3->s0 plus removal of the four leading ASM_KEEP fences
   restores the 0x28 prologue/save order and fills the first branch delay.
   A named state-zero base, v0-pinned tail bases, split page, and zero-arg
   func_800A6D30 prevent RMW commoning and collapse the +1-word cascade. */
