#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80700B50;
extern M2C_UNK D_80700B5C;
extern M2C_UNK D_80700B64;
extern M2C_UNK D_80700B74;
extern M2C_UNK D_80700B88;
extern s32 D_8070139C;
extern s32 D_807013A4;
extern void *D_807013B4;

void func_80701194(s32 *arg0) {
    s32 *var_a2;
    s32 *var_a3;

    var_a3 = &D_8070139C;
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
    M2C_FIELD(D_807013B4, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x68)(&D_80700B50, &D_80700B5C, M2C_FIELD(arg0, s32 *, 8), var_a3);
    M2C_FIELD(D_807013B4, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x68)(&D_80700B50, &D_80700B64, D_807013A4);
    M2C_FIELD(D_807013B4, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32, s32 *), 0x68)(&D_80700B74, &D_80700B88, 0x30);
}
