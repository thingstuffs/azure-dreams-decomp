#include "common.h"
#include "m2c_compat.h"

s32 func_800A6D30();                                /* extern */
extern M2C_UNK D_8001F6F8;
extern M2C_UNK D_80073414;

s16 func_8001EAA4(s8 *arg0, s8 *arg1) {
    s16 var_a2;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a3;
    s8 var_t0;
    u16 *var_v1;
    u16 temp_v1;
    u16 var_t1;
    u32 temp_a0;
    u32 temp_a1;
    void *temp_a3;

    temp_a0 = (u32) (func_800A6D30() & 0xFFFF) % (u16) M2C_FIELD(&D_8001F6F8, u16 *, 0x26);
    var_a2 = 1;
    var_v1 = &D_8001F6F8 + 2;
    temp_a1 = temp_a0 & 0xFFFF;
loop_1:
    var_t0 = 1;
    if ((u16) *var_v1 < temp_a1) {
        var_a2 += 1;
        var_v1 += 2;
        if (var_a2 >= 0x13) {
            var_t0 = 1;
        } else {
            goto loop_1;
        }
    }
    var_a1 = var_a2 * 4;
    temp_a3 = (var_a2 * 0x14) + &D_80073414;
    var_t1 = M2C_FIELD((&D_8001F6F8 + (var_a2 * 2)), u16 *, -2);
    if ((s32) M2C_FIELD(temp_a3, u8 *, 2) > 1) {
        var_a3 = 0x14;
loop_6:
        temp_v1 = *(var_a3 + M2C_FIELD((((var_a1 + var_a2) * 4) + &D_80073414), s32 *, 0xC));
        if (!(temp_v1 & 0x10)) {
            if (!(temp_v1 & 0x40) || (var_a1 = var_a2 * 4, (*(s32 *)0x80012090 == 2))) {
                temp_v1_2 = ((s32) (*(var_a3 + M2C_FIELD(temp_a3, s32 *, 0xC)) & 0x3000) / 4096) & 3;
                var_a1_2 = 0x80;
                if (temp_v1_2 != 0) {
                    var_a1_2 = 0x55;
                    if (temp_v1_2 != 1) {
                        var_a1_2 = 1;
                        if (temp_v1_2 == 2) {
                            var_a1_2 = 0x20;
                        }
                    }
                }
                var_t1 += var_a1_2;
                if (temp_a0 < (u32) (var_t1 & 0xFFFF)) {
                    *arg0 = (s8) var_a2;
                    *arg1 = var_t0;
                    return var_a2;
                }
                goto block_15;
            }
            goto block_16;
        }
block_15:
        var_a1 = var_a2 * 4;
block_16:
        var_t0 += 1;
        var_a3 += 0x14;
        if (var_t0 >= (s32) M2C_FIELD((((var_a1 + var_a2) * 4) + &D_80073414), u8 *, 2)) {
            goto block_17;
        }
        goto loop_6;
    }
block_17:
    *arg0 = 0;
    *arg1 = 0;
    return 0;
}
