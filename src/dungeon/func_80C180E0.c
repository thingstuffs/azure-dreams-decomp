#include "common.h"

typedef struct S_801738E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_801738E0_0;   /* arg0 in func_801738E0 */

typedef struct S_801738E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801738E0_1;   /* arg2 in func_801738E0 */

typedef struct S_801738E0_2 {
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
} S_801738E0_2;   /* arg3 in func_801738E0 */

typedef struct S_801738E0_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_801738E0_3;   /* arg1 in func_801738E0 */

typedef struct S_801738E0_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801738E0_4;   /* D_800814A8 in func_801738E0 */

typedef struct S_801738E0_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_801738E0_5;   /* origin in func_801738E0 */



struct GlobalStruct {
    u16 unk0;
    u16 flags;
    u8 unk4[6];
    u16 counter;
};

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
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
extern void func_80174250(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern struct GlobalStruct D_80083460;
extern void *D_80170858[];
extern u8 D_801713A8[];
extern u8 D_8017449C[];
extern u8 D_801744EC[];
extern u8 D_801744F4[];
extern u8 D_801744FC[];

void func_801738E0(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    void *arg0 = in_arg0;
    void *arg1 = in_arg1;
    register void *arg2 ASM_REG("$18") = in_arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *arg3 = in_arg3;
    static void *const sw_keep[] = {
        &&state_zero, &&state_one, &&state_two, &&state_three,
        &&state_four, &&done, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&state_sixteen,
    };
    struct GlobalStruct *global_base;
    register u8 *table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    u32 clear_mask;
    u32 flags;
    u8 state;

#ifndef __mips__
#endif

    state = ((S_801738E0_0 *)arg0)->unk_9B;
    if (state >= 17U) {
        goto done;
    }
    (void)sw_keep;
    goto *D_80170858[state];

state_zero:
    if (((S_801738E0_1 *)arg2)->unk_14 & 0x8000) {
        ((S_801738E0_0 *)arg0)->unk_90 = 0;
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_801744FC;
        func_80047784(
            arg2,
            D_801744FC[
                ((D_80083228 + ((S_801738E0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        goto state_to_two;
    }
    ((S_801738E0_0 *)arg0)->unk_98 |= 8;
    ((S_801738E0_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_801738E0_2 *)arg3)->unk_1C &= 0xFFFBFFFF;
    if (!(((S_801738E0_1 *)arg2)->unk_14 & 0x6000)) {
        goto done;
    }
    {
        register s32 val ASM_REG("$2") = 0xFFF80000;   /* MATCH pin: retail schedule: same instructions, different order without it */
        table = D_801744F4;
        ((S_801738E0_3 *)arg1)->unk_14 = val;
    }
    goto play_and_advance;

state_one:
    if (((S_801738E0_3 *)arg1)->unk_14 <= 0xFFFFF) {
        ((S_801738E0_3 *)arg1)->unk_14 += 0x20000;
    }
    if (((S_801738E0_0 *)arg0)->unk_90 < 0) {
        goto done;
    }
    ((S_801738E0_0 *)arg0)->unk_90 = 0;
    ((S_801738E0_3 *)arg1)->unk_14 = 0;
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_801744FC;
    func_80047784(
        arg2,
        D_801744FC[
            ((D_80083228 + ((S_801738E0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_800A9A0C(arg3);

state_to_two:
    {
        register struct GlobalStruct *g ASM_REG("$3") = &D_80083460;   /* MATCH pin: retail register colouring depends on it */
        g->counter--;
    }
    ((S_801738E0_0 *)arg0)->unk_9B = 2;
    goto done;

state_two:
    ((S_801738E0_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_801738E0_2 *)arg3)->unk_1C |= 0x08000000;
    if ((func_80042900(arg3, 1) << 16) == 0) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_801744F4;
        func_80047784(
            arg2,
            D_801744F4[
                ((D_80083228 + ((S_801738E0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        flags = ((S_801738E0_2 *)arg3)->unk_1C | 0x40000;
        ((S_801738E0_2 *)arg3)->unk_1C = flags;
        if (((S_801738E0_1 *)arg2)->unk_14 & 0x8000) {
            clear_mask = ~0x200U;
            goto clear_200;
        }
        {
            register struct GlobalStruct *g ASM_REG("$2") = &D_80083460;   /* MATCH pin: retail schedule: same instructions, different order without it */
            register u16 c = g->counter + 1;
            ASM_KEEP_NV(c);   /* MATCH pin: retail immediate-load split depends on it */
            g->counter = c;
        }
        goto advance_state;
    }

    global_base = &D_80083460;
    if (global_base->flags & 0x1000) {
        goto done;
    }
    if (((S_801738E0_2 *)arg3)->unk_64 != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if (((S_801738E0_2 *)arg3)->unk_25 == 0) {
        if (global_base->flags & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, arg1, arg2, arg3);
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = ((S_801738E0_2 *)arg3)->unk_1C;
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        ((S_801738E0_0 *)arg0)->unk_A8 = 0;
        func_80174250(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (((S_801738E0_2 *)arg3)->unk_6D == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(
                 arg3, (u8 *)((S_801738E0_4 *)D_800814A8)->unk_58 + 0x20)
             << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 coordinate = ((S_801738E0_1 *)arg2)->unk_26;

        if ((((coordinate == ((S_801738E0_5 *)origin)->unk_26) && (coordinate >= 0)) ||
             (func_8009FD40(origin, arg2) < 2)) &&
            ((func_800A6D30() & 7) == 0)) {
            func_80042B68(arg3, 1);
        }
    }
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }

    (*(void * *)((u8 *)arg2 + 0x2C)) = D_801744F4;
    func_80047784(
        arg2,
        D_801744F4[
            ((D_80083228 + ((S_801738E0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    flags = ((S_801738E0_2 *)arg3)->unk_1C | 0x40000;
    ((S_801738E0_2 *)arg3)->unk_1C = flags;
    if (((S_801738E0_1 *)arg2)->unk_14 & 0x8000) {
        clear_mask = ~0x200U;
        goto clear_200;
    }
    {
        register struct GlobalStruct *g ASM_REG("$2") = &D_80083460;   /* MATCH pin: retail schedule: same instructions, different order without it */
        g->counter++;
    }
    goto advance_state;

state_three:
    if (!(((S_801738E0_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    table = D_801744EC;

play_and_advance:
    (*(void * *)((u8 *)arg2 + 0x2C)) = table;
    func_80047784(
        arg2,
        *(u8 *)((((D_80083228 + ((S_801738E0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7) + (u32)table),
        0);

advance_state:
    ((S_801738E0_0 *)arg0)->unk_9B++;
    goto done;

state_four:
    if (!(((S_801738E0_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_801738E0_3 *)arg1)->unk_14 = 0xFFF80000;
    ((S_801738E0_0 *)arg0)->unk_A8 = 8;
    ((S_801738E0_0 *)arg0)->unk_98 &= 0xBFFF;
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_8017449C;
    func_80047784(
        arg2,
        D_8017449C[
            ((D_80083228 + ((S_801738E0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801738E0_0 *)arg0)->unk_98 |= 8;
    ((S_801738E0_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_801738E0_0 *)arg0)->unk_9B = 0x10;
    goto done;

state_sixteen:
    if (!(((S_801738E0_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_801738E0_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_801738E0_2 *)arg3)->unk_1C |= 0x08000000;
    ((S_801738E0_0 *)arg0)->unk_98 |= 0x4000;
    ((S_801738E0_3 *)arg1)->unk_14 = 0;
    {
        struct GlobalStruct *g = &D_80083460;
        g->counter--;
    }
    ((S_801738E0_2 *)arg3)->unk_1C &= ~0x200;
    ((S_801738E0_0 *)arg0)->unk_8C = D_801713A8;
    goto done;

clear_200:
    ((S_801738E0_2 *)arg3)->unk_1C = clear_mask & flags;
    ((S_801738E0_0 *)arg0)->unk_8C = D_801713A8;

done:
    return;
}
