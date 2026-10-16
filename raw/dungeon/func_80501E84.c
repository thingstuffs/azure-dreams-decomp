#include "common.h"
#include "m2c_compat.h"

s32 func_80019894(M2C_UNK);                         /* extern */
M2C_UNK func_8003E4FC(M2C_UNK, s32, M2C_UNK);       /* extern */
M2C_UNK func_8003F320(s32);                         /* extern */
M2C_UNK func_8004425C(M2C_UNK);                     /* extern */
M2C_UNK func_8004450C(s16);                         /* extern */
M2C_UNK func_80044698(s32 *);                       /* extern */
M2C_UNK func_80053DA8(M2C_UNK);                     /* extern */
extern M2C_UNK D_8006E704;
extern s8 D_80080AF3;
extern M2C_UNK D_80080AF4;
extern s16 D_80080AFC;
extern M2C_UNK D_801BEE40;
extern M2C_UNK D_801C4640;

s32 func_80019684(s32 arg0, s16 arg1, s32 arg2) {
    M2C_UNK *var_v0_2;
    M2C_UNK var_a0;
    s16 temp_v1;
    s32 **temp_s0;
    s32 *temp_a0;
    s32 *temp_a0_2;
    s32 *temp_a1;
    s32 *temp_s0_2;
    s32 temp_a0_3;
    s32 var_v0;
    u16 var_s5;

    var_s5 = 0;
    temp_s0 = ((s32) (arg0 << 0x10) >> 0xE) + &D_8006E704;
    if (*temp_s0 == *((D_80080AFC * 4) + &D_80080AF4)) {
        return 1;
    }
    var_v0 = arg2 << 0x10;
    if ((func_80019894(1) << 0x10) != 0) {
        func_8004425C(0xC);
        var_v0 = arg2 << 0x10;
    }
    if (var_v0 == 0) {
        var_s5 = (u16) D_80080AFC;
    }
    temp_a0 = *temp_s0;
    temp_v1 = (u16) D_80080AFC ^ 1;
    D_80080AFC = temp_v1;
    if (temp_a0 != *(((s32) (temp_v1 << 0x10) >> 0xE) + &D_80080AF4)) {
        if (D_80080AF3 != arg1) {
            func_80044698(temp_a0);
        }
        temp_a0_2 = *temp_s0;
        *temp_a0_2 &= 0xFF800000;
        temp_a1 = *temp_s0;
        if (D_80080AFC != 0) {
            var_v0_2 = &D_801C4640;
        } else {
            var_v0_2 = &D_801BEE40;
        }
        *temp_a1 |= (s32) var_v0_2 & 0x7FFFFF;
        temp_s0_2 = ((s32) (arg0 << 0x10) >> 0xE) + &D_8006E704;
        func_8003E4FC(6, *temp_s0_2, 0);
        temp_a0_3 = *temp_s0_2;
        *((D_80080AFC * 4) + &D_80080AF4) = temp_a0_3;
        func_8003F320(temp_a0_3);
    }
    func_8004450C(arg1);
    if ((arg2 << 0x10) != 0) {
        var_a0 = 0x21;
        if (D_80080AFC != 0) {
            var_a0 = 0x22;
        }
        func_80053DA8(var_a0);
        return 0;
    }
    D_80080AFC = (s16) var_s5;
    return 0;
}
