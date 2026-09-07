#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern u8 D_80083160[];

void func_80016BF0(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    register s16 held_arg2 ASM_REG("$16") = arg2;
    s32 temp_a3;
    s32 temp_v1_3;
    s32 temp_t6;
    s32 temp_t5;
    s32 var_a1;
    s32 var_t1;
    u32 temp_a2;
    u8 *temp_v1;
    u8 *temp_t4;
    u8 *temp_v1_2;
    u8 *temp_v1_6;
    void *temp_a0;
    void *temp_t0;
    u8 *temp_base;
    void *temp_v1_4;
    void *temp_v1_5;

    temp_base = D_80083160;
    temp_t0 = temp_base + 0x1DC;
    temp_v1 = FIELD(temp_t0, u8 *, 0x10);
    if (temp_v1 != 0) {
        var_t1 = 0;
        temp_t6 = FIELD(temp_base, s32, 0x1DC);
        temp_t4 = temp_v1;
        if ((arg3 << 0x10) > 0) {
            do {
                var_a1 = 0;
                if (arg2 > 0) {
                    temp_a3 = arg1 + var_t1;
                    temp_t5 = held_arg2;
                    do {
                        temp_a0 = (void *)(temp_t6 + (((temp_a3 << FIELD(temp_t0, s16, 0x14)) + arg0 + var_a1) * 6));
                        temp_a2 = FIELD(temp_a0, u16, 0);
                        temp_v1_2 = temp_t4 + temp_a2;
                        if (*temp_v1_2 & 1) {
                            FIELD(temp_a0, u16, 4) = (u16)(FIELD(temp_a0, u16, 4) | 1);
                        }
                        if (*temp_v1_2 & 4) {
                            FIELD(temp_a0, u16, 4) = (u16)(FIELD(temp_a0, u16, 4) | 4);
                        }
                        if (*temp_v1_2 & 8) {
                            FIELD(temp_a0, u16, 4) = (u16)(FIELD(temp_a0, u16, 4) | 8);
                        }
                        if (*temp_v1_2 & 0x20) {
                            FIELD(temp_a0, u16, 4) = (u16)(FIELD(temp_a0, u16, 4) | 0x400);
                        }
                        temp_v1_3 = var_a1 + arg0;
                        if (*temp_v1_2 & 2) {
                            if (temp_v1_3 > 0) {
                                FIELD(temp_a0, u16, -2) = (u16)(FIELD(temp_a0, u16, -2) | 1);
                            }
                            if (temp_v1_3 < ((1 << FIELD(temp_t0, s16, 0x14)) - 1)) {
                                FIELD(temp_a0, u16, 0xA) = (u16)(FIELD(temp_a0, u16, 0xA) | 1);
                            }
                            if (temp_a3 > 0) {
                                temp_v1_4 = (void *)((((0 - (1 << FIELD(temp_t0, s16, 0x14))) * 6)) + (u32)temp_a0);
                                FIELD(temp_v1_4, u16, 4) = (u16)(FIELD(temp_v1_4, u16, 4) | 1);
                            }
                            if (temp_a3 < ((1 << FIELD(temp_t0, s16, 0x16)) - 1)) {
                                temp_v1_5 = (u8 *)temp_a0 + (6 << FIELD(temp_t0, s16, 0x14));
                                FIELD(temp_v1_5, u16, 4) = (u16)(FIELD(temp_v1_5, u16, 4) | 1);
                            }
                        }
                        temp_v1_6 = temp_t4 + temp_a2;
                        if (*temp_v1_6 & 0x80) {
                            FIELD(temp_a0, u16, 4) = (u16)(FIELD(temp_a0, u16, 4) | 0x8000);
                        }
                        if (*temp_v1_6 & 0x40) {
                            FIELD(temp_a0, u16, 4) = (u16)(FIELD(temp_a0, u16, 4) | 0x40);
                        }
                        var_a1 += 1;
                    } while (var_a1 < temp_t5);
                }
                var_t1 += 1;
            } while (var_t1 < arg3);
        }
    }
    ASM_KEEP(held_arg2);
}

/* MECHANISM: The 8-byte leaf frame preserves arg2 in pinned s0; the body
   holds the D_80083160 base through the early branch and hoists its 0x1dc
   table pointer before both nested loops. The map pointer and signed inner
   bound split v1->t4 and s0->t5; BASE[index] fixes the neighbor addu order. */
