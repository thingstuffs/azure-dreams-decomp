#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_800A9C18(void *, void *, void *, s16); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
M2C_UNK func_8015EB50(void *, void *, void *, M2C_UNK); /* extern */
M2C_UNK func_80161C30();                            /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8015F12C;
extern M2C_UNK D_8015F514;
extern M2C_UNK D_80161E8C;
extern void *D_80162710;

void *func_8015EF84(s16 arg0, s8 arg1, s8 arg2, u16 arg3) {
    u16 temp_s2;
    u16 temp_s3;
    u16 temp_v0_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *var_s4;

    var_s4 = NULL;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s4 = temp_v0 + 0x20;
        D_80162710 = temp_v0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8015F12C;
        M2C_FIELD(var_s4, s8 *, 0x13) = 0x37;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, u16 *, 0xA) = arg3;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s8 *, 0x24) = arg1;
        M2C_FIELD(temp_s0, s8 *, 0x25) = arg2;
        M2C_FIELD(temp_s0, M2C_UNK **, 0x2C) = &D_80161E8C;
        M2C_FIELD(var_s4, s16 *, 0x9E) = 0;
        func_800A9C18(temp_v0, temp_s1, temp_s0, arg0);
        M2C_FIELD(var_s4, s8 *, 0x9A) = 0xFF;
        M2C_FIELD(var_s4, s8 *, 0x9C) = -1;
        M2C_FIELD(var_s4, M2C_UNK **, 0x8C) = &D_8015F514;
        M2C_FIELD(var_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s4, s32 *, 0x1C) | 0x40000);
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        func_800AA36C(var_s4, temp_s1, temp_s0, var_s4);
        temp_v0_2 = *(u16 *)0x8008378A;
        M2C_FIELD(temp_s1, u16 *, 0xA) = temp_v0_2;
        M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (temp_v0_2 - 0x20);
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) (temp_v0_2 - 0x190);
        temp_s2 = M2C_FIELD(temp_s0, u16 *, 0x1C);
        temp_s3 = M2C_FIELD(temp_s0, u16 *, 0x1E);
        M2C_FIELD(temp_s0, u16 *, 0x1C) = 0U;
        M2C_FIELD(temp_s0, u16 *, 0x1E) = 0U;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x80);
        func_8015EB50(var_s4, temp_s1, temp_s0, 1);
        func_8015EB50(var_s4, temp_s1, temp_s0, 2);
        M2C_FIELD(temp_s0, u16 *, 0x1C) = temp_s2;
        M2C_FIELD(temp_s0, u16 *, 0x1E) = temp_s3;
        func_80161C30();
    }
    return var_s4;
}
