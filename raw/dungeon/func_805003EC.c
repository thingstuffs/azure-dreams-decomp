#include "common.h"
#include "m2c_compat.h"

s32 func_80017EBC(s16);                             /* extern */
s16 func_80017F88(s16, s16 *, s16 *, M2C_UNK);      /* extern */
s16 func_8001816C(s16, s16 *, s16 *, M2C_UNK);      /* extern */
s32 func_80018304(s16, s16, s16, s16);              /* extern */
s16 func_800BCB04(s32, s32, M2C_UNK, s16);          /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8008333C;

s32 func_80017BEC(s16 arg0) {
    s16 sp10;
    s16 sp12;
    s16 sp18;
    s16 *var_s1;
    s16 *var_s2;
    s16 temp_a1;
    s16 temp_a2;
    s16 var_s0;
    s16 var_s4;
    s16 var_s5;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_s7;
    s32 temp_v0_2;
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;
    u16 temp_v1;
    void *temp_a0;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v0_4;

    temp_s7 = M2C_FIELD(&D_8008333C, s32 *, 0);
    sp18 = arg0;
    var_s4 = func_80017F88(arg0, &sp10, &sp12, 0);
    if (var_s4 >= 0x200) {
        goto block_1;
    }
    temp_v0 = ((sp10 + (sp12 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s7;
    M2C_FIELD(temp_v0, u16 *, 4) = (u16) (M2C_FIELD(temp_v0, u16 *, 4) | 0x100);
    var_s6 = func_80017EBC(arg0);
loop_3:
    var_s5 = -1;
    var_s3 = 0;
    var_s0 = 7;
    var_s2 = &D_8006CCE8 + 0xE;
    var_s1 = &D_8006CCD8 + 0xE;
    do {
        if ((func_80018304(sp10, sp12, var_s4, var_s0) << 0x10) != 0) {
            temp_a0 = ((sp10 + *var_s1 + ((sp12 + *var_s2) << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s7;
            temp_v1 = M2C_FIELD(temp_a0, u16 *, 4);
            if (!(temp_v1 & 0x100)) {
                M2C_FIELD(temp_a0, u16 *, 4) = (u16) (temp_v1 | 0x200);
                var_s5 = var_s0;
            }
            var_s3 += 1;
        }
        var_s2 -= 2;
        var_s0 -= 1;
        var_s1 -= 2;
    } while (var_s0 >= 0);
    if (var_s3 != 0) {
        temp_v0_2 = var_s5 * 2;
        if (var_s5 >= 0) {
            temp_a2 = (u16) sp10 + *(temp_v0_2 + &D_8006CCD8);
            temp_a1 = (u16) sp12 + *(temp_v0_2 + &D_8006CCE8);
            temp_v0_3 = ((temp_a2 + (temp_a1 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s7;
            temp_a0_2 = var_s6 - 1;
            var_s6 = temp_a0_2;
            sp10 = temp_a2;
            sp12 = temp_a1;
            M2C_FIELD(temp_v0_3, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_3, u16 *, 4) | 0x100);
            if ((temp_a0_2 << 0x10) > 0) {
                var_s4 = func_800BCB04(((temp_a2 << 6) + 0x20) & 0xFFE0, ((temp_a1 << 6) + 0x20) & 0xFFE0, -0x400, temp_a2);
                goto loop_3;
            }
            goto block_15;
        }
        var_s4 = func_8001816C((s16) (u16) sp18, &sp10, &sp12, 1);
        var_v0 = 0;
        if (var_s4 < 0x200) {
            temp_v0_4 = ((sp10 + (sp12 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s7;
            temp_a0_3 = var_s6 - 1;
            var_s6 = temp_a0_3;
            M2C_FIELD(temp_v0_4, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_4, u16 *, 4) | 0x100);
            if ((temp_a0_3 << 0x10) <= 0) {
block_15:
                var_v0 = 1;
                /* Duplicate return node #16. Try simplifying control flow for better match */
                return var_v0;
            }
            goto loop_3;
        }
        return var_v0;
    }
block_1:
    return 0;
}
