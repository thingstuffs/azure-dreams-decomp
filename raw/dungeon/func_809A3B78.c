#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8(s32);                             /* extern */
s32 func_80064584(s32);                             /* extern */
s32 func_80065420(M2C_UNK, s32, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_8006658C(void *, s32);                 /* extern */
M2C_UNK func_80067F20(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
s16 func_80069EF8();                                /* extern */

s32 func_80175378(void *arg0, void *arg1) {
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 var_a0;
    s16 var_a0_2;
    s16 var_s5;
    s16 var_t0;
    s16 var_v1;
    s32 temp_s0;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s8 temp_a0;
    u8 temp_v0_2;
    void *temp_s0_2;
    void *temp_v1;
    void *var_s1;

    var_s5 = 0;
    var_s3 = M2C_FIELD(*(void **)0x80083160, s32 *, 0x8D0);
    M2C_FIELD(arg0, u8 *, 0xF) = 0U;
    *(void **)0x1F800020 = *(void **)0x80083160 + 0xB0;
    *(void **)0x1F800000 = (u16) M2C_FIELD(arg1, u16 *, 2);
    *(void **)0x1F800002 = (u16) M2C_FIELD(arg1, u16 *, 6);
    var_s1 = var_s3 + 7;
    *(void **)0x1F800004 = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    var_v0 = 0 << 0x10;
    do {
        temp_v1 = arg0 + (var_v0 >> 0x10);
        temp_v0_2 = M2C_FIELD(temp_v1, u8 *, 0x10) + 4;
        M2C_FIELD(temp_v1, u8 *, 0x10) = temp_v0_2;
        var_s0 = var_s5 << 0x10;
        if ((s8) temp_v0_2 >= 0x30) {
            if (M2C_FIELD(arg0, u8 *, 0xE) != 0) {
                M2C_FIELD(temp_v1, u8 *, 0x10) = 0x30U;
            } else {
                M2C_FIELD(temp_v1, u8 *, 0x10) = 0U;
                var_s0 = var_s5 << 0x10;
                goto block_5;
            }
        } else {
block_5:
            M2C_FIELD(var_s1, s32 *, -3) = 0;
            M2C_FIELD(var_s1, s32 *, 5) = 0;
            temp_s0 = var_s0 >> 0x10;
            temp_v1_2 = *(void **)0x1F800000 + ((s32) (func_80064584((temp_s0 + (M2C_FIELD(arg0, s16 *, 0xC) << 6)) << 7) * 0x10) >> 0xB);
            *(void **)0x1F800070 = temp_v1_2;
            *(void **)0x1F800078 = temp_v1_2;
            temp_s0_2 = arg0 + temp_s0;
            temp_v1_3 = *(void **)0x1F800002 + ((s32) (func_800644B8((temp_s0 + (M2C_FIELD(arg0, s16 *, 0xC) << 6)) << 7) * 0x10) >> 0xB);
            *(void **)0x1F800072 = temp_v1_3;
            *(void **)0x1F80007A = temp_v1_3;
            temp_v0_3 = *(void **)0x1F800004 - (M2C_FIELD(temp_s0_2, s8 *, 0x10) * 2);
            *(void **)0x1F800074 = temp_v0_3;
            *(void **)0x1F80007C = (s16) (temp_v0_3 + 0x40);
            temp_a0 = M2C_FIELD(temp_s0_2, s8 *, 0x10);
            var_v1 = func_80069EF8();
            if (temp_a0 >= 0x21) {
                var_v0_2 = temp_a0 - 0x20;
                goto block_9;
            }
            if (temp_a0 < 0x10) {
                var_v0_2 = 0x10 - temp_a0;
block_9:
                var_v1 = (s16) (var_v1 / var_v0_2);
            }
            var_a0 = 0;
            if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 1) {
                var_a0 = var_v1;
            }
            M2C_FIELD(var_s1, s8 *, 0xD) = (s8) var_a0;
            M2C_FIELD(var_s1, s8 *, 0x15) = (s8) var_a0;
            var_a0_2 = 0;
            if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 4) {
                var_a0_2 = var_v1;
            }
            M2C_FIELD(var_s1, s8 *, 0xE) = (s8) var_a0_2;
            M2C_FIELD(var_s1, s8 *, 0x16) = (s8) var_a0_2;
            var_t0 = 0;
            if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 2) {
                var_t0 = var_v1;
            }
            M2C_FIELD(var_s1, s8 *, 0xF) = (s8) var_t0;
            M2C_FIELD(var_s1, s8 *, 0x17) = (s8) var_t0;
            *(void **)0x1F8000C0 = func_80065420(0x1F800000, var_s3 + 8, 0x1F800090, 0x1F800094);
            M2C_FIELD(var_s1, s32 *, 9) = (s32) M2C_FIELD(var_s1, s32 *, 1);
            M2C_FIELD(var_s1, s32 *, 9) = (s16) ((u16) M2C_FIELD(var_s1, s32 *, 9) + 4);
            *(void **)0x1F8000C0 += func_80065420(0x1F800000, var_s3 + 0x18, 0x1F800090, 0x1F800094);
            M2C_FIELD(var_s1, s32 *, 0x19) = (s32) M2C_FIELD(var_s1, s32 *, 0x11);
            M2C_FIELD(var_s1, s32 *, 0x19) = (s16) ((u16) M2C_FIELD(var_s1, s32 *, 0x19) + 2);
            temp_s3 = var_s3 + 0x24;
            *(void **)0x1F8000C0 = (s32) *(void **)0x1F8000C0 >> 1;
            M2C_FIELD(var_s1, s8 *, -4) = 8;
            M2C_FIELD(var_s1, s8 *, 0) = 0x3A;
            var_s1 = var_s1 + 0x24 + 0xC;
            func_8006658C(*(void **)0x1F800020 + (*(void **)0x1F8000C0 * 4), var_s3);
            func_80067F20(temp_s3, 0, 0, 0x60, 0);
            func_8006658C(*(void **)0x1F800020 + (*(void **)0x1F8000C0 * 4), temp_s3);
            var_s3 = temp_s3 + 0xC;
            M2C_FIELD(arg0, u8 *, 0xF) = (u8) (M2C_FIELD(arg0, u8 *, 0xF) + 1);
        }
        temp_v0 = var_s5 + 1;
        var_s5 = temp_v0;
        var_v0 = var_s5 << 0x10;
    } while (temp_v0 < 0x20);
    M2C_FIELD(*(void **)0x80080000, s32 *, 0x8D0) = var_s3;
    return 0;
}
