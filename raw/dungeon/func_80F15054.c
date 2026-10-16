#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80044A50(void *);                      /* extern */
M2C_UNK func_800A48F0(void *, M2C_UNK, s32);        /* extern */
s32 func_800A6D30(void *);                          /* extern */
M2C_UNK func_800A9C18(void *, void *, void *, s16); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
M2C_UNK func_800BC318(void *);                      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80164A8C;
extern M2C_UNK D_80164F74;
extern M2C_UNK D_80167D30;
extern M2C_UNK D_80167D78;

void *func_80164854(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 temp_v0_2;
    s32 var_s5;
    s32 var_v0;
    s32 var_v1;
    void *temp_s0;
    void *temp_s2;
    void *temp_s6;
    void *temp_v0;
    void *var_s1;

    var_s1 = NULL;
    var_s5 = 1;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80164A8C;
        M2C_FIELD(var_s1, s8 *, 0x13) = 0x23;
        func_8004491C(temp_v0, &D_80045340);
        temp_s6 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s6, s16 *, 0xA) = arg3;
        temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s2, s8 *, 0x25) = arg2;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_80167D30;
        temp_v0_2 = arg0 & 3;
        M2C_FIELD(temp_s2, s8 *, 0x24) = arg1;
        if (temp_v0_2 == 1) {
            var_v0 = M2C_FIELD(var_s1, s32 *, 0x14) | 0x6000;
            var_v1 = M2C_FIELD(var_s1, s32 *, 0x1C) | 0x6000;
            goto block_5;
        }
        if (temp_v0_2 >= 2) {
            var_v0 = M2C_FIELD(var_s1, s32 *, 0x14) | 0x2000;
            var_v1 = M2C_FIELD(var_s1, s32 *, 0x1C) | 0x2000;
block_5:
            M2C_FIELD(var_s1, s32 *, 0x14) = var_v0;
            M2C_FIELD(var_s1, s32 *, 0x1C) = var_v1;
        } else if (((arg0 & ~3) << 0x10) == 0) {
            if (!(M2C_FIELD(var_s1, s32 *, 0x14) & 0x200) && (func_800A6D30(temp_v0) & 1)) {
                M2C_FIELD(var_s1, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s1, s32 *, 0x1C) | 0x200);
                func_800A48F0(var_s1, 1, (func_800A6D30() & 0x3F) | 0x20);
                M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_80167D78;
            }
            var_s5 = func_800A6D30() & 3;
        }
        func_800A9C18(temp_v0, temp_s6, temp_s2, arg0);
        M2C_FIELD(var_s1, s8 *, 0x9A) = 0xFF;
        M2C_FIELD(var_s1, s8 *, 0x9C) = -1;
        M2C_FIELD(var_s1, M2C_UNK **, 0x8C) = &D_80164F74;
        M2C_FIELD(var_s1, s16 *, 0xA4) = -1;
        if (var_s5 != 0) {
            M2C_FIELD(var_s1, s16 *, 0xA6) = 0;
        } else {
            temp_s0 = var_s1 - 0x20;
            M2C_FIELD(var_s1, s16 *, 0xA6) = 1;
            M2C_FIELD(temp_s2, s16 *, 0x10) = 0x60;
            M2C_FIELD(temp_s2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x14) | 0xC);
            M2C_FIELD(temp_s2, u16 *, 0x12) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x12) - 0x80);
            func_80044A50(temp_s0);
            func_800BC318(temp_s0);
        }
        func_800AA36C(var_s1, temp_s6, temp_s2, var_s1);
    }
    return var_s1;
}
