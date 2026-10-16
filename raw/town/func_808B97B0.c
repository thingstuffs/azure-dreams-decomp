#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_A0700140;
extern M2C_UNK D_A070014C;
extern M2C_UNK D_A0700154;
extern M2C_UNK D_A0700164;
extern M2C_UNK D_A0700178;
extern s32 D_A0700B38;
extern s32 D_A0700B40;
extern void *D_A0700B50;

void func_A07007B0(s32 *arg0) {
    s32 *var_a2;
    s32 *var_a3;

    var_a3 = &D_A0700B38;
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
    M2C_FIELD(D_A0700B50, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x64)(&D_A0700140, &D_A070014C, M2C_FIELD(arg0, s32 *, 8), var_a3);
    M2C_FIELD(D_A0700B50, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x64)(&D_A0700140, &D_A0700154, D_A0700B40);
    M2C_FIELD(D_A0700B50, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x64)(&D_A0700164, &D_A0700178, 0x30);
    M2C_FIELD(D_A0700B50, M2C_UNK (**)(M2C_UNK), 0x6C)(0);
}
