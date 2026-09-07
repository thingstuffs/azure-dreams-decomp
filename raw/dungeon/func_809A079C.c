#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

s32 func_80171F9C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register s32 held_arg1 ASM_REG("$22") = arg1;
    s32 neg;
    s32 mode;
    u16 old_value;
    register u16 flags_value ASM_REG("$2");
    u8 status;
    u16 remaining;

    ASM_KEEP(held_arg1);
    status = *(volatile u8 *)((u8 *)arg3 + 0x71);
    {
        void *held_arg2 = arg2;
        register s32 obj ASM_REG("$18");
        register u16 *flags ASM_REG("$21");
        register u8 *page ASM_REG("$2");

        *(volatile u8 *)((u8 *)arg3 + 0x71) = status & 0x7F;
        ASM_SCHED_BARRIER();
        page = (u8 *)0x80080000;
        ASM_KEEP(page);
        flags = (u16 *)(page + 0x3460);
        ASM_KEEP(flags);
        mode = 0;
        if (flags[1] & 0x2000) {
            return -1;
        }

        obj = func_800A04F0(arg3, FIELD(held_arg2, u8, 0x24), FIELD(held_arg2, u8, 0x25), FIELD(arg3, s16, 0x2A));
        if ((func_800A2CB8(arg3, obj) << 16) == 0) {
            return 0;
        }
        if (flags[1] & 0x2000) {
            return -1;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000) && (flags[1] & 8)) {
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
            register s32 m ASM_REG("$3") = mode;
            FIELD(arg0, s8, 0x9B) = 0;
            if (m == 1) {
                FIELD(arg0, s32, 0x8C) = 0;
                FIELD(held_arg2, u8 *, 0x2C) = D_80175E50;
                flags_value = FIELD(arg0, u16, 0x98);
                FIELD(arg0, s8, 0x9A) = 0x11;
                goto set_flag;
            }
            if (m == 2) {
                FIELD(arg0, s32, 0x8C) = 0;
                FIELD(held_arg2, u8 *, 0x2C) = D_80175E70;
                flags_value = FIELD(arg0, u16, 0x98);
                FIELD(arg0, s8, 0x9A) = 0x17;
set_flag:
                FIELD(arg0, u16, 0x98) = flags_value | 8;
                FIELD(arg3, s8, 0x84) = 0x7C;
                FIELD(arg3, s8, 0x85) = 0;
                goto common;
            }

            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(held_arg2, u8 *, 0x2C) = D_80175EA8;
            FIELD(arg0, s8, 0x9A) = 0x18;
            FIELD(arg3, s8, 0x84) = 0x7C;
            FIELD(arg3, s8, 0x85) = 0;
            FIELD(arg3, s32, 0x1C) &= 0xFFFBFFFF;

common:
            {
                register u8 *phase_page ASM_REG("$2");
                phase_page = (u8 *)0x80080000;
                ASM_KEEP(phase_page);
                func_80047784(held_arg2, FIELD(held_arg2, u8 *, 0x2C)[((*(s16 *)(phase_page + 0x3228) + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7], 0);
            }
            FIELD(arg3, u8, 0x6D)--;
            func_8009C93C(arg3, held_arg2, FIELD(arg3, s16, 0x2A), 1, 0);
            remaining = FIELD(arg0, u16, 0x92);
            old_value = FIELD(arg0, u16, 0xA2);
            FIELD(arg0, u16, 0xA2) = 0;
            FIELD(arg0, s16, 0x9E) = 0;
            FIELD(arg0, u16, 0x92) = remaining - old_value;
            return mode;
        }
    }
}
