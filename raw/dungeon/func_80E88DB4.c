#include "common.h"
#include "m2c_compat.h"

u8 func_800A6DA4(M2C_UNK, s32);                     /* extern */
extern M2C_UNK D_80073414;

s32 func_801505B4(void *arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_s5;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 temp_a1;
    u8 temp_v0;
    u8 temp_v0_2;
    void *temp_s0;

    var_s4 = 0;
    var_s3 = 0xF;
    temp_s5 = *((M2C_FIELD(arg0, u8 *, 0) * 0x14) + M2C_FIELD(((M2C_FIELD(arg0, u8 *, 1) * 0x14) + &D_80073414), s32 *, 0xC)) & 0x3000;
loop_1:
    temp_v0 = func_800A6DA4(1, 0x13);
    temp_a0 = temp_v0 & 0xFF;
    temp_s0 = (temp_a0 * 0x14) + &D_80073414;
    if ((M2C_FIELD(temp_s0, u8 *, 2) != 1) && (temp_a0 != 0x12) && (temp_a0 != 0xE)) {
        temp_v0_2 = func_800A6DA4(1, (M2C_FIELD(temp_s0, u8 *, 2) - 1) & 0xFFFF);
        if (!(*(((temp_v0_2 & 0xFF) * 0x14) + M2C_FIELD(temp_s0, s32 *, 0xC)) & 0x10)) {
            if (var_s3 >= 0xC) {
                var_v0 = var_s4;
                if (temp_s5 == (*((M2C_FIELD(arg0, u8 *, 0) * 0x14) + M2C_FIELD(((M2C_FIELD(arg0, u8 *, 1) * 0x14) + &D_80073414), s32 *, 0xC)) & 0x3000)) {
                    var_s4 = 1;
                    goto block_10;
                }
            } else {
                var_v0 = var_s4;
                if (temp_s5 >= (*((M2C_FIELD(arg0, u8 *, 0) * 0x14) + M2C_FIELD(((M2C_FIELD(arg0, u8 *, 1) * 0x14) + &D_80073414), s32 *, 0xC)) & 0x3000)) {
                    var_s4 = 1;
block_10:
                    var_v0 = 1;
                }
            }
            if (var_v0 != 0) {
                M2C_FIELD(arg0, u8 *, 1) = temp_v0;
                M2C_FIELD(arg0, u8 *, 0) = temp_v0_2;
                M2C_FIELD(arg0, s8 *, 2) = 0;
                M2C_FIELD(arg0, s8 *, 3) = 0;
                if ((temp_v0 & 0xFF) == 4) {
                    M2C_FIELD(arg0, s8 *, 3) = 0x80;
                    var_v0_2 = 1;
                    if ((temp_v0_2 & 0xFF) != 0x11) {
                        temp_a1 = M2C_FIELD(arg1, u8 *, 0x25);
                        var_v0_3 = temp_a1 + 0xF;
                        if (var_v0_3 < 0) {
                            var_v0_3 = temp_a1 + 0x1E;
                        }
                        var_v0_2 = var_v0_3 >> 4;
                    }
                    M2C_FIELD(arg0, s8 *, 2) = (s8) var_v0_2;
                }
                return 1;
            }
            goto block_19;
        }
    }
block_19:
    var_s3 -= 1;
    if (var_s3 < 0) {
        return 0;
    }
    goto loop_1;
}
