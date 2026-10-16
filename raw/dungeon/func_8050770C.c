#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(M2C_UNK *, s32, M2C_UNK);     /* extern */
M2C_UNK func_80042640(void *, u8);                  /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
void *(*func_800A0B94(u8, s32, M2C_UNK))(M2C_UNK, u8, u8, M2C_UNK); /* extern */
M2C_UNK func_800A152C(u8, M2C_UNK);                 /* extern */
s32 func_800A1618(u8, M2C_UNK);                     /* extern */
M2C_UNK func_800A1D4C(void *, M2C_UNK);             /* extern */
s32 func_800A4E2C(u8 *, u8 *);                      /* extern */
s8 func_800A6D30(u8 *);                             /* extern */
u8 func_800A6DA4(M2C_UNK, M2C_UNK);                 /* extern */
s16 func_800BCB04(s32, s32, M2C_UNK);               /* extern */
extern s32 D_800735C4;
extern M2C_UNK D_80081468;
extern u16 D_8008146C;
extern M2C_UNK D_800835E4;
extern M2C_UNK D_800835E8;
extern M2C_UNK D_800DF258;
extern s32 D_800E296C;
extern M2C_UNK D_800E3648;
extern M2C_UNK D_800E39C8;
extern s32 D_800E3D6C;

void func_8001EF0C(void) {
    u8 sp10;
    u8 sp11;
    M2C_UNK *var_s1;
    M2C_UNK *var_s2;
    M2C_UNK *var_s2_2;
    M2C_UNK *var_s3;
    s16 temp_v0_4;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s3_2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s5;
    u16 temp_v1_4;
    u32 temp_v1;
    u8 temp_s1;
    u8 temp_v0_3;
    u8 var_s0;
    u8 var_v0;
    u8 var_v1;
    void *temp_v0_2;

    var_s4 = 0;
    var_s2 = &D_800E3648;
    var_s3 = &D_800E39C8;
    do {
        if (M2C_FIELD(var_s2, u8 *, 1) == 0x13) {
            temp_s1 = M2C_FIELD(var_s2, u8 *, 0);
            temp_v0 = func_800A1618(temp_s1, 1);
            if (temp_v0 != 0) {
                temp_v0_2 = func_800A0B94(temp_s1, temp_v0, 1)(0, M2C_FIELD(var_s3, u8 *, 6), M2C_FIELD(var_s3, u8 *, 7), -0x400);
                if (temp_v0_2 != NULL) {
                    func_800A152C(temp_s1, 1);
                    func_80042640(temp_v0_2, temp_s1);
                    M2C_FIELD(temp_v0_2, s8 *, 0x43) = 0xFF;
                    M2C_FIELD(temp_v0_2, s8 *, 0x12) = 0;
                    temp_v1 = *((M2C_FIELD(var_s2, s8 *, 2) * 4) + &D_800835E4);
                    M2C_FIELD(temp_v0_2, u32 *, 0x18) = temp_v1;
                    if (temp_v1 >= (u32) *((M2C_FIELD(temp_v0_2, u8 *, 0x11) * 4) + (&D_800835E4 + 4))) {
                        do {
                            func_800A1D4C(temp_v0_2, 0);
                        } while ((u32) M2C_FIELD(temp_v0_2, u32 *, 0x18) >= (u32) *((M2C_FIELD(temp_v0_2, u8 *, 0x11) * 4) + &D_800835E8));
                    }
                    M2C_FIELD(temp_v0_2, s8 *, 0x43) = func_800A6D30();
                }
            }
            M2C_FIELD(var_s2, u8 *, 0) = 0;
        }
        var_s2 += 4;
        var_s4 += 1;
        var_s3 += 0x18;
    } while (var_s4 < 0x20);
    if (M2C_FIELD(&D_80081468, s16 *, 6) == 1) {
        var_s5 = (func_800A6D30() & 3) + 4;
    } else {
        var_s5 = ((s16) (u16) M2C_FIELD(&D_80081468, s16 *, 6) / 2) + (func_800A6D30() & 3);
    }
    if (var_s5 >= 0x21) {
        var_s5 = 0x20;
    }
    var_s4_2 = 0;
    var_s1 = &D_800E39C8;
    var_s2_2 = &D_800E3648;
    var_s3_2 = ((s16) D_8008146C / 2) + (func_800A6D30() & 0x3F);
    do {
        if (M2C_FIELD(var_s2_2, u8 *, 1) == 0x15) {
            sp10 = M2C_FIELD(var_s1, u8 *, 6);
            sp11 = M2C_FIELD(var_s1, u8 *, 7);
            var_s0 = M2C_FIELD(var_s2_2, u8 *, 0);
            var_v0 = M2C_FIELD(var_s2_2, u8 *, 2);
            var_v1 = M2C_FIELD(var_s2_2, u8 *, 3);
            goto block_27;
        }
        if (!(D_800E3D6C & 8) && (var_s4_2 < var_s5)) {
            M2C_FIELD(var_s2_2, u8 *, 1) = 0U;
            M2C_FIELD(var_s2_2, u8 *, 0) = 0U;
            var_s3_2 += func_800A6D30() & 0xF;
            temp_v0_3 = func_800A6DA4(1, 0x13);
            var_s0 = temp_v0_3;
            temp_v1_2 = *(((var_s0 & 0xFF) * 0xC) + D_800735C4) & 0x3000;
            if (temp_v1_2 != 0x3000) {
                temp_v1_3 = ((u32) (temp_v1_2 << 0x10) >> 0x1A) + 4;
                if ((var_s3_2 >= temp_v1_3) && ((var_s3_2 -= temp_v1_3, ((D_800E296C & 0x20000000) != 0)) || ((u32) ((var_s0 - 0xF) & 0xFF) >= 2U))) {
                    M2C_FIELD(var_s2_2, u8 *, 1) = 0x15U;
                    M2C_FIELD(var_s2_2, u8 *, 0) = temp_v0_3;
                    do {

                    } while (func_800A4E2C(&sp10, &sp11) & 0x8000);
                    M2C_FIELD(var_s1, u8 *, 6) = sp10;
                    M2C_FIELD(var_s1, u8 *, 7) = sp11;
                    var_v0 = (func_800A6D30(&sp10) & 7) | 4;
                    var_v1 = 0x80;
block_27:
                    M2C_FIELD(var_s2_2, u8 *, 2) = var_v0;
                    M2C_FIELD(var_s2_2, u8 *, 3) = var_v1;
                    temp_v0_4 = func_800BCB04((sp10 << 6) | 0x20, (sp11 << 6) | 0x20, -0x400);
                    M2C_FIELD(var_s1, s16 *, 0x12) = temp_v0_4;
                    M2C_FIELD(var_s1, s16 *, 0x10) = temp_v0_4;
                    M2C_FIELD(var_s1, u16 *, 0x14) = 0U;
                    func_8009A21C(sp10, sp11, 0x20);
                    temp_s0 = *(((var_s0 & 0xFF) * 4) + &D_800DF258);
                    if (temp_s0 < 0) {
                        func_8003DB94(var_s1, temp_s0, 0);
                        temp_v1_4 = M2C_FIELD(var_s1, u16 *, 0x14);
                        M2C_FIELD(var_s1, u16 *, 0x14) = (u16) (temp_v1_4 | 0x840);
                        if (temp_s0 & 0x20000000) {
                            M2C_FIELD(var_s1, u16 *, 0x14) = (u16) (temp_v1_4 | 0x940);
                        }
                    } else {
                        if (temp_s0 != 0) {
                            M2C_FIELD(var_s1, s32 *, 8) = (s32) (temp_s0 | 0x80000000);
                        }
                        M2C_FIELD(var_s1, u16 *, 0x14) = (u16) (M2C_FIELD(var_s1, u16 *, 0x14) | 0x800);
                    }
                    M2C_FIELD(var_s1, s32 *, 0xC) = 0;
                }
            }
        }
        var_s1 += 0x18;
        var_s4_2 += 1;
        var_s2_2 += 4;
    } while (var_s4_2 < 0x20);
}
