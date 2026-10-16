#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_800A48F0(void *, M2C_UNK, s32);        /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800A9C18(void *, void *, void *, s16); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80152A58;
extern M2C_UNK D_80152E5C;
extern M2C_UNK D_80156510;
extern M2C_UNK D_80156538;

void *func_80152854(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 temp_v1;
    void *temp_s1;
    void *temp_s6;
    void *temp_v0;
    void *var_s0;

    var_s0 = NULL;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s0 = temp_v0 + 0x20;
        M2C_FIELD(var_s0, s8 *, 0x13) = 0x1C;
        func_8004491C(temp_v0, &D_80045340);
        temp_s6 = M2C_FIELD(temp_v0, void **, 8);
        temp_v1 = arg0 & 3;
        M2C_FIELD(temp_s6, s16 *, 0xA) = arg3;
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s8 *, 0x25) = arg2;
        M2C_FIELD(temp_s1, s8 *, 0x24) = arg1;
        if (temp_v1 == 1) {
            M2C_FIELD(var_s0, M2C_UNK **, 0x8C) = &D_80152E5C;
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x6000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x6000);
        } else if (temp_v1 >= 2) {
            M2C_FIELD(var_s0, M2C_UNK **, 0x8C) = &D_80152E5C;
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x2000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x2000);
        } else if (((arg0 & ~3) << 0x10) == 0) {
            if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200) && (func_800A6D30() & 1)) {
                func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                M2C_FIELD(temp_s1, M2C_UNK **, 0x2C) = &D_80156538;
            }
            M2C_FIELD(var_s0, M2C_UNK **, 0x8C) = &D_80152E5C;
        } else {
            M2C_FIELD(var_s0, M2C_UNK **, 0x8C) = &D_80152E5C;
        }
        M2C_FIELD(temp_s1, M2C_UNK **, 0x2C) = &D_80156510;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80152A58;
        func_800A9C18(temp_v0, temp_s6, temp_s1, arg0);
        M2C_FIELD(var_s0, s8 *, 0x9A) = 0xFF;
        M2C_FIELD(var_s0, s8 *, 0x9C) = -1;
        func_800AA36C(var_s0, temp_s6, temp_s1, var_s0);
    }
    return var_s0;
}
