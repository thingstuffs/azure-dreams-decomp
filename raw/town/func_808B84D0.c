#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_000034D0;
extern M2C_UNK D_000034DC;
extern M2C_UNK D_000034E4;
extern M2C_UNK D_000034F4;
extern M2C_UNK D_00003508;
extern s32 D_000045F8;

void func_80003CD0(s32 *arg0) {
    s32 *var_a2;
    s32 *var_a3;

    var_a3 = &D_000045F8;
    var_a2 = arg0;
    do {
        M2C_FIELD(var_a3, s32 *, 0) = M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
        M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
        var_a2 += 0x10;
        var_a3 += 0x10;
    } while (var_a2 != (arg0 + 0x30));
    *var_a3 = *var_a2;
    M2C_FIELD(*(void **)0x4610, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x64)(&D_000034D0, &D_000034DC, M2C_FIELD(arg0, s32 *, 8), var_a3);
    M2C_FIELD(*(void *)0x4610, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x64)(&D_000034D0, &D_000034E4, *(s32 *)0x4600);
    M2C_FIELD(*(void *)0x4610, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x64)(&D_000034F4, &D_00003508, 0x2F);
    M2C_FIELD(*(void *)0x4610, M2C_UNK (**)(M2C_UNK), 0x6C)(0);
}
