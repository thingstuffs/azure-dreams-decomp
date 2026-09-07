#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80048FBC();
s32 func_80049004();
s32 func_800491CC();
extern s32 D_8002E5E8[];

s32 func_800B44F0(void *arg0, s32 arg1)
{
    register s32 *temp_v1 ASM_REG("$3");
    s32 temp_s2;
    register s32 temp_v0 ASM_REG("$2");
    s32 temp_v0_2;
    s32 var_s1;

    var_s1 = 0;
    temp_s2 = arg0 + 0x60;
    temp_v0 = func_80049004(temp_s2, arg1, 0xC);
    ASM_KEEP(temp_v0);
    M2C_FIELD(arg0, s32 *, 0x5C) = temp_v0;
    if (temp_v0 != 0) {
        register s32 call_arg ASM_REG("$4") = temp_v0;

        ASM_KEEP(call_arg);
        temp_v1 = D_8002E5E8;
        M2C_FIELD(arg0, s32 *, 0x40) = D_8002E5E8[0];
        M2C_FIELD(arg0, s32 *, 0x44) = M2C_FIELD(temp_v1, s32 *, 4);
        M2C_FIELD(arg0, s32 *, 0x48) = M2C_FIELD(temp_v1, s32 *, 8);
        func_800491CC(call_arg, arg0 + 0x40, 0x21);
        temp_v0_2 = func_80048FBC(temp_s2, 0xC);
        var_s1 = temp_v0_2 != 0;
        M2C_FIELD(arg0, s32 *, 0x20) = temp_v0_2;
    }
    return var_s1;
}
