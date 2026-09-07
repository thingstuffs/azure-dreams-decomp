#include "common.h"

typedef struct S_80171F9C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171F9C_0;   /* held_arg2 in func_80171F9C */

typedef struct S_80171F9C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x16];
    s8 unk_84;
    s8 unk_85;
} S_80171F9C_1;   /* arg3 in func_80171F9C */

typedef struct S_80171F9C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80171F9C_2;   /* arg0 in func_80171F9C */



extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern u8 D_80175E50[];
extern u8 D_80175E70[];
extern u8 D_80175EA8[];

s32 func_80171F9C(S_80171F9C_2 *arg0, s32 arg1, void *arg2, void *arg3) {
    register s32 held_arg1 ASM_REG("$22") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 neg;
    s32 mode;
    u16 old_value;
    register u16 flags_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 status;
    u16 remaining;

    ASM_KEEP(held_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    status = *(volatile u8 *)((u8 *)arg3 + 0x71);
    {
        S_80171F9C_0 *held_arg2 = arg2;
        register s32 obj ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
        register u16 *flags ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
        register u8 *page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        *(volatile u8 *)((u8 *)arg3 + 0x71) = status & 0x7F;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        page = (u8 *)0x80080000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        flags = (u16 *)(page + 0x3460);
        ASM_KEEP(flags);   /* MATCH pin: keeps a statement from moving across a call/branch */
        mode = 0;
        if (flags[1] & 0x2000) {
            return -1;
        }

        obj = func_800A04F0(arg3, held_arg2->unk_24, held_arg2->unk_25, ((S_80171F9C_1 *)arg3)->unk_2A);
        if ((func_800A2CB8(arg3, obj) << 16) == 0) {
            return 0;
        }
        if (flags[1] & 0x2000) {
            return -1;
        }
        if (!(((S_80171F9C_1 *)arg3)->unk_46 & 0x8000) && (flags[1] & 8)) {
            return -1;
        }

        neg = 0 - func_800A0134(obj, arg3);
        if ((u32)((neg - 0x20) & 0xFFFF) < 0x21U) {
            mode = 1;
            goto check_ready;
        }
        if ((u32)((neg + 0x10) & 0xFFFF) < 0x31U) {
            mode = 2;
            goto check_ready;
        }
        if ((u32)((neg + 0x40) & 0xFFFF) >= 0x31U) {
            return mode;
        }
        mode = 3;

check_ready:
        if ((func_800A2B5C(arg3) << 16) != 0) {
            return -1;
        }
        func_800C7930((u8 *)arg3 - 0x20, held_arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 16) != 0) {
            return -1;
        }

        {
            register s32 m ASM_REG("$3") = mode;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            arg0->unk_9B = 0;
            if (m == 1) {
                arg0->unk_8C = 0;
                held_arg2->unk_2C = D_80175E50;
                flags_value = arg0->unk_98;
                arg0->unk_9A = 0x11;
                goto set_flag;
            }
            if (m == 2) {
                arg0->unk_8C = 0;
                held_arg2->unk_2C = D_80175E70;
                flags_value = arg0->unk_98;
                arg0->unk_9A = 0x17;
set_flag:
                arg0->unk_98 = flags_value | 8;
                ((S_80171F9C_1 *)arg3)->unk_84 = 0x7C;
                ((S_80171F9C_1 *)arg3)->unk_85 = 0;
                goto common;
            }

            arg0->unk_8C = 0;
            held_arg2->unk_2C = D_80175EA8;
            arg0->unk_9A = 0x18;
            ((S_80171F9C_1 *)arg3)->unk_84 = 0x7C;
            ((S_80171F9C_1 *)arg3)->unk_85 = 0;
            ((S_80171F9C_1 *)arg3)->unk_1C &= 0xFFFBFFFF;

common:
            {
                u8 *phase_page;
                phase_page = (u8 *)0x80080000;
                func_80047784(held_arg2, held_arg2->unk_2C[((*(s16 *)(phase_page + 0x3228) + ((S_80171F9C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
            }
            ((S_80171F9C_1 *)arg3)->unk_6D--;
            func_8009C93C(arg3, held_arg2, ((S_80171F9C_1 *)arg3)->unk_2A, 1, 0);
            remaining = arg0->unk_92;
            old_value = arg0->unk_A2;
            arg0->unk_A2 = 0;
            arg0->unk_9E = 0;
            arg0->unk_92 = remaining - old_value;
            return mode;
        }
    }
}
