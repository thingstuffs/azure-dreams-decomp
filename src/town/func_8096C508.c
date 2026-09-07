#include "common.h"

typedef struct {
    u8 pad0[8];
    u32 field_8;
    u8 padC[4];
    u32 field_10;
} GlobalState;

typedef struct {
    void *field_0;
    s16 field_4;
    s16 field_6;
    u8 pad8[2];
    u8 field_A;
    u8 field_B;
    u8 padC[3];
    u8 field_F;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 pad14;
    u8 field_15;
    u8 field_16;
    u8 field_17[2];
    u8 pad19[0x43];
} Object;

extern GlobalState D_80083160;
extern u8 D_80082E6B;
extern int D_800814A0;
extern s8 D_80080A84;
extern s8 D_80129728;

extern u8 func_80123200(u8);
extern void func_80053DA8(s32);
extern void func_801237A4(Object *);
extern void func_80044144(s32, s32, s32, s32);
extern void func_8004B248(void *);
extern void func_801231DC(void);

void func_801249A0(Object *arg0)
{
    GlobalState *state = &D_80083160;
    u32 flags;
    register u32 tail_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 other;
    u8 second;
    u8 wanted;
    s32 i;
    s32 **table;

    flags = state->field_10;
    if (flags & 0x40) {
        s32 slot;
        register Object *call_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

        if (!func_80123200(arg0->field_13)) {
            goto end;
        }
        func_80053DA8(0x702);
        slot = arg0->field_16;
        wanted = arg0->field_13;
        other = *((u8 *)arg0 + slot + 0x17);
        if (other == wanted) {
            goto matched_six;
        }
        slot ^= 1;
        second = *((u8 *)arg0 + slot + 0x17);
        if (second != wanted) {
            goto check_five;
        }
        call_arg = arg0;
        arg0->field_16 = slot;
        func_801237A4(call_arg);
matched_six:
        arg0->field_A = 6;
        arg0->field_4 = 1;
        arg0->field_6 = 0x19;
        goto end;
check_five:
        if (other == 0xFF) {
            goto matched_five;
        }
        if (second == 0xFF) {
            call_arg = arg0;
            arg0->field_16 = slot;
            func_801237A4(call_arg);
        }
matched_five:
        arg0->field_A = 5;
        arg0->field_B = 0;
        goto end;
    }

    if (flags & 0x20) {
        func_80053DA8(0x700);
        if (D_80082E6B == 0x17) {
            func_80044144(0, 0, 0, 0);
            table = (s32 **)&D_80129728;
            for (i = 0; i < 98; i++) {
                *table[i] = 0;
            }
            *(u16 *)((u8 *)arg0->field_0 + 0x1E) |= 0x2000;
            func_8004B248((u8 *)arg0 + 0x5C);
            *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_801231DC();
            D_80080A84 = 2;
            goto end;
        }
    }

    flags = state->field_10;
    if (flags & 0x8000) {
        u8 mode;

        if (arg0->field_10 == 0) {
            (*(volatile u8 *)&arg0->field_F) += 3;
            (*(volatile u8 *)&arg0->field_F) &= 3;
        }
        mode = arg0->field_F;
        arg0->field_10 ^= 1;
        if ((mode == 3) && (arg0->field_15 != 0)) {
            arg0->field_F = 2;
        }
        arg0->field_A = 0;
        goto end;
    }
    if (flags & 0x2000) {
        u8 mode;

        if (arg0->field_10 != 0) {
            (*(volatile u8 *)&arg0->field_F) += 1;
            (*(volatile u8 *)&arg0->field_F) &= 3;
        }
        mode = arg0->field_F;
        arg0->field_10 ^= 1;
        if ((mode == 3) && (arg0->field_15 != 0)) {
            arg0->field_F = 0;
        }
        arg0->field_A = 0;
        goto end;
    }

    flags = state->field_8;
    if (flags & 0x1000) {
        if (arg0->field_F == 3) {
            goto reset_four;
        }
        {
            u32 raw_toggle;
            s32 saved_toggle;

            raw_toggle = 1;
            (*(volatile s16 *)&arg0->field_4) = raw_toggle;
            raw_toggle = arg0->field_11;
            saved_toggle = raw_toggle;
            ASM_KEEP(saved_toggle);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            *(volatile u8 *)&arg0->field_11 = raw_toggle + 7;
            arg0->field_6 = 4;
            (*(volatile u8 *)&arg0->field_11) &= 7;
            arg0->field_12 = saved_toggle;
        }
        if ((*(volatile u8 *)&arg0->field_11) != 7) {
            goto set_two;
        }
        tail_value = arg0->field_10;
        arg0->field_A = 3;
        goto toggle;
    }
    if (!(flags & 0x4000)) {
        goto end;
    }
    {
        u32 raw_toggle;
        s32 saved_toggle;
        register s32 one ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */

        one = 1;
        if (arg0->field_F == 3) {
            goto reset_four;
        }
        raw_toggle = arg0->field_11;
        saved_toggle = raw_toggle;
        ASM_KEEP(saved_toggle);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        *(volatile u8 *)&arg0->field_11 = raw_toggle + 1;
        arg0->field_4 = one;
        (*(volatile u8 *)&arg0->field_11) &= 7;
        arg0->field_12 = saved_toggle;
    }
    arg0->field_6 = 4;
    if ((*(volatile u8 *)&arg0->field_11) != 0) {
        goto set_two;
    }
    tail_value = arg0->field_10;
    ASM_KEEP(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    arg0->field_A = 3;
    goto toggle;

set_two:
    arg0->field_A = 2;
    goto end;
reset_four:
    tail_value = 1;
    arg0->field_4 = tail_value;
    tail_value = arg0->field_10;
    arg0->field_6 = 4;
    arg0->field_A = 4;
toggle:
    arg0->field_10 = tail_value ^ 1;
end:
    return;
}
