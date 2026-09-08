#include "common.h"

typedef struct S_80016BF0_0 {
    u8 pad_00[0x10];
    u8 * unk_10;
    s16 unk_14;
    s16 unk_16;
} S_80016BF0_0;   /* temp_t0 in func_80016BF0 */

typedef struct S_80016BF0_1 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
} S_80016BF0_1;   /* temp_base in func_80016BF0 */

typedef struct S_80016BF0_2_pre {
    u16 unk_00;
} S_80016BF0_2_pre;   /* the 0x2 bytes before temp_a0 in func_80016BF0, addressed as temp_a0[-1] */

typedef struct S_80016BF0_2 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    u8 pad_06[0x4];
    u16 unk_0A;
} S_80016BF0_2;   /* temp_a0 in func_80016BF0 */

typedef struct S_80016BF0_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80016BF0_3;   /* temp_v1_4 in func_80016BF0 */

typedef struct S_80016BF0_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80016BF0_4;   /* temp_v1_5 in func_80016BF0 */



extern u8 D_80083160[];

void func_80016BF0(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    register s16 held_arg2 ASM_REG("$16") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
    S_80016BF0_0 *temp_t0;
    u8 *temp_base;
    S_80016BF0_3 *temp_v1_4;
    S_80016BF0_4 *temp_v1_5;

    temp_base = D_80083160;
    temp_t0 = temp_base + 0x1DC;
    temp_v1 = temp_t0->unk_10;
    if (temp_v1 != 0) {
        var_t1 = 0;
        temp_t6 = ((S_80016BF0_1 *)temp_base)->unk_1DC;
        temp_t4 = temp_v1;
        if ((arg3 << 0x10) > 0) {
            do {
                var_a1 = 0;
                if (arg2 > 0) {
                    temp_a3 = arg1 + var_t1;
                    temp_t5 = held_arg2;
                    do {
                        temp_a0 = (void *)(temp_t6 + (((temp_a3 << temp_t0->unk_14) + arg0 + var_a1) * 6));
                        temp_a2 = ((S_80016BF0_2 *)temp_a0)->unk_00;
                        temp_v1_2 = temp_t4 + temp_a2;
                        if (*temp_v1_2 & 1) {
                            ((S_80016BF0_2 *)temp_a0)->unk_04 = (u16)(((S_80016BF0_2 *)temp_a0)->unk_04 | 1);
                        }
                        if (*temp_v1_2 & 4) {
                            ((S_80016BF0_2 *)temp_a0)->unk_04 = (u16)(((S_80016BF0_2 *)temp_a0)->unk_04 | 4);
                        }
                        if (*temp_v1_2 & 8) {
                            ((S_80016BF0_2 *)temp_a0)->unk_04 = (u16)(((S_80016BF0_2 *)temp_a0)->unk_04 | 8);
                        }
                        if (*temp_v1_2 & 0x20) {
                            ((S_80016BF0_2 *)temp_a0)->unk_04 = (u16)(((S_80016BF0_2 *)temp_a0)->unk_04 | 0x400);
                        }
                        temp_v1_3 = var_a1 + arg0;
                        if (*temp_v1_2 & 2) {
                            if (temp_v1_3 > 0) {
                                ((S_80016BF0_2_pre *)temp_a0)[-1].unk_00 = (u16)(((S_80016BF0_2_pre *)temp_a0)[-1].unk_00 | 1);
                            }
                            if (temp_v1_3 < ((1 << temp_t0->unk_14) - 1)) {
                                ((S_80016BF0_2 *)temp_a0)->unk_0A = (u16)(((S_80016BF0_2 *)temp_a0)->unk_0A | 1);
                            }
                            if (temp_a3 > 0) {
                                temp_v1_4 = (void *)((((0 - (1 << temp_t0->unk_14)) * 6)) + (u32)temp_a0);
                                temp_v1_4->unk_04 = (u16)(temp_v1_4->unk_04 | 1);
                            }
                            if (temp_a3 < ((1 << temp_t0->unk_16) - 1)) {
                                temp_v1_5 = (u8 *)temp_a0 + (6 << temp_t0->unk_14);
                                temp_v1_5->unk_04 = (u16)(temp_v1_5->unk_04 | 1);
                            }
                        }
                        temp_v1_6 = temp_t4 + temp_a2;
                        if (*temp_v1_6 & 0x80) {
                            ((S_80016BF0_2 *)temp_a0)->unk_04 = (u16)(((S_80016BF0_2 *)temp_a0)->unk_04 | 0x8000);
                        }
                        if (*temp_v1_6 & 0x40) {
                            ((S_80016BF0_2 *)temp_a0)->unk_04 = (u16)(((S_80016BF0_2 *)temp_a0)->unk_04 | 0x40);
                        }
                        var_a1 += 1;
                    } while (var_a1 < temp_t5);
                }
                var_t1 += 1;
            } while (var_t1 < arg3);
        }
    }
    ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: The 8-byte leaf frame preserves arg2 in pinned s0; the body
   holds the D_80083160 base through the early branch and hoists its 0x1dc
   table pointer before both nested loops. The map pointer and signed inner
   bound split v1->t4 and s0->t5; BASE[index] fixes the neighbor addu order. */
