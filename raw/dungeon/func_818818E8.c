#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80025270(void) __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern s16 func_800BCB04(u16, u16, s16);

extern u16 D_800257CE[5];
extern s32 D_800814A0[3];

__asm__(".set D_800257CE, 0x800257CE");

void func_800250E8(void *arg0, void *arg1, void *arg2)
{
    register void *tail_arg ASM_REG("$19");
    s32 temp_v0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0_8;
    register s32 temp_v1 ASM_REG("$3");
    s32 temp_lo;
    s32 random_value;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 call_arg0;
    s32 call_arg1;
    s16 call_arg2;
    u16 counter;
    u16 *counter_ptr;

    tail_arg = arg2;
    ASM_KEEP_NV(tail_arg);
    counter_ptr = D_800257CE;
    call_arg0 = FIELD(arg1, u16, 2);
    counter = counter_ptr[0];
    call_arg2 = FIELD(arg1, u16, 0xA);
    call_arg1 = FIELD(arg1, u16, 6);
    counter++;
    call_arg2 -= 2;
    counter_ptr[0] = counter;
    if (FIELD(arg1, s16, 0xA) <
        func_800BCB04(call_arg0, call_arg1, call_arg2)) {
        if (FIELD(arg0, s16, 0x26) == 0) {
            temp_s0 = func_80064584(FIELD(arg0, s16, 0x1A));
            FIELD(arg1, s32, 0) = (s32)(FIELD(arg1, s32, 0) +
                (((s32)(temp_s0 * FIELD(arg0, s16, 0x1C)) >> 4) +
                 (func_80069EF8() & 0xFFFF)));

            temp_s0_2 = func_800644B8(FIELD(arg0, s16, 0x1A));
            temp_a0 = ((temp_s0_2 * FIELD(arg0, s16, 0x1C)) >> 4) +
                       (func_80069EF8() & 0xFFFF);
            FIELD(arg1, s32, 4) = (s32)(FIELD(arg1, s32, 4) + temp_a0);

            random_value = func_80069EF8();
            FIELD(arg1, s32, 8) = (s32)(FIELD(arg1, s32, 8) +
                (0xFFFE0000 - (random_value & 0xFFF)));
            func_80025270();
            return;
        }

        FIELD(arg1, s32, 0) = (s32)(FIELD(arg1, s32, 0) +
            func_80064584(FIELD(arg0, s16, 0x1A)) *
            FIELD(arg0, s16, 0x1C) * 8);
        temp_lo = func_800644B8(FIELD(arg0, s16, 0x1A)) *
                  FIELD(arg0, s16, 0x1C);
        temp_a0_2 = FIELD(arg1, s32, 0x14);
        temp_v1 = temp_a0_2;
        ASM_KEEP_NV(temp_v1);
        temp_v0_8 = FIELD(arg1, s32, 8);
        FIELD(arg1, s32, 0x14) = temp_v1 + 0x6000;
        FIELD(arg1, s32, 8) = (s32)(temp_v0_8 + temp_a0_2);
        FIELD(arg1, s32, 4) = (s32)(FIELD(arg1, s32, 4) + temp_lo * 8);
    }

    temp_v0 = FIELD(arg0, u16, 0x1C) - 1;
    FIELD(arg0, s16, 0x1C) = temp_v0;
    if ((temp_v0 << 16) <= 0 ||
        (FIELD(tail_arg, u16, 0x14) & 0x8000)) {
        FIELD(arg0, u16, -2) = (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
