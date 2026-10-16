#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
s32 func_800A4E2C(u8 *, u8 *);                      /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A6DA4(M2C_UNK, s32);                    /* extern */
s16 func_800A71F4();                                /* extern */
s32 func_800A7A38(void *);                          /* extern */
s16 func_800BCA68(s32, s32, u8, u8);                /* extern */
extern s16 D_8008146C;
extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;

void func_8001EC54(void) {
    u8 sp10;
    u8 sp11;
    M2C_UNK *var_a0;
    M2C_UNK *var_v1;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_s3;
    s32 var_s3_2;
    s8 var_s0;
    s8 var_s2;
    s8 var_s4;
    s8 var_s5;
    void *temp_s0;
    void *temp_s1;

    if (*(s32 *)0x80012090 == 2) {
        var_s3 = D_8008146C * 0xC8;
    } else {
        var_s3 = 0x4B;
        if (D_8008146C >= 0xC) {
            var_s3 = 0x2BC;
            if (D_8008146C < 0x16) {
                var_s3 = 0xC8;
            }
        }
    }
    if (func_800A6D30() & 1) {
        var_s3_2 = var_s3 + (func_800A6DA4(0, (var_s3 / 2) & 0xFFFF) & 0xFFFF);
    } else {
        var_s3_2 = var_s3 - (func_800A6DA4(0, (var_s3 / 2) & 0xFFFF) & 0xFFFF);
    }
    if (var_s3_2 >= 0) {
loop_10:
        temp_v0 = func_800A71F4();
        if (temp_v0 >= 0) {
            if (var_s3_2 >= 0x12D) {
                temp_v0_2 = func_800A6DA4(0xA0, 0xF0);
                var_s2 = temp_v0_2 & 0xFFFF;
                var_s4 = 1;
                var_s0 = 3;
                var_s5 = (temp_v0_2 & 0xFFFF) / 10;
            } else if (var_s3_2 >= 0x97) {
                var_s2 = func_800A6DA4(0x50, 0x78) & 0xFFFF;
                var_s5 = var_s2;
                var_s4 = 0;
                var_s0 = 2;
            } else {
                var_s2 = func_800A6DA4(0x10, 0x18) & 0xFFFF;
                var_s5 = var_s2;
                var_s4 = 0;
                var_s0 = 1;
            }
            do {

            } while (func_800A4E2C(&sp10, &sp11) & 0x8000);
            var_a1 = 0;
            var_v1 = &D_800E36C8;
            var_a0 = &D_800E3548;
loop_19:
            if ((M2C_FIELD(var_a0, u8 *, 1) == 0) || (M2C_FIELD(var_v1, u8 *, 0) != sp10) || (M2C_FIELD(var_v1, u8 *, 1) != sp11)) {
                var_v1 += 0xC;
                var_a1 += 1;
                var_a0 += 4;
                if (var_a1 >= 0x40) {

                } else {
                    goto loop_19;
                }
            }
            if (var_a1 == 0x40) {
                temp_s1 = (temp_v0 * 4) + &D_800E3548;
                M2C_FIELD(temp_s1, s8 *, 0) = var_s0;
                M2C_FIELD(temp_s1, s8 *, 1) = 0xE;
                M2C_FIELD(temp_s1, s8 *, 3) = var_s4;
                M2C_FIELD(temp_s1, s8 *, 2) = var_s5;
                temp_s0 = (temp_v0 * 0xC) + &D_800E36C8;
                M2C_FIELD(temp_s0, u8 *, 0) = sp10;
                M2C_FIELD(temp_s0, u8 *, 1) = sp11;
                temp_v0_3 = func_800BCA68((sp10 << 6) | 0x20, (sp11 << 6) | 0x20, sp11, sp10);
                M2C_FIELD(temp_s0, s8 *, 7) = 0;
                M2C_FIELD(temp_s0, s16 *, 4) = temp_v0_3;
                func_8009A21C(sp10, sp11, 0x800);
                M2C_FIELD(temp_s0, s32 *, 8) = func_800A7A38(temp_s1);
            }
            var_s3_2 -= var_s2;
            if (var_s3_2 >= 0) {
                goto loop_10;
            }
        }
    }
}
