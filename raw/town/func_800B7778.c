#include "common.h"

extern s32 func_80049004();
extern s32 func_800491CC();
extern s32 func_8004B404();
extern s32 D_8002E5E8[];

s32 func_800B4ED8(void *arg0, s32 arg1) {
    register s32 *temp_v1 ASM_REG("$3");
    register s32 call_arg ASM_REG("$4");
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;

    var_s1 = 0;
    temp_v0 = func_80049004((s8 *)arg0 + 0x60, arg1, 0xC);
    *(s32 *)((s8 *)arg0 + 0x5C) = temp_v0;
    if (temp_v0 != 0) {
        call_arg = temp_v0;
        ASM_KEEP(call_arg);
        temp_v1 = D_8002E5E8;
        *(s32 *)((s8 *)arg0 + 0x40) = D_8002E5E8[0];
        *(s32 *)((s8 *)arg0 + 0x44) = temp_v1[1];
        *(s32 *)((s8 *)arg0 + 0x48) = temp_v1[2];
        func_800491CC(call_arg, (s8 *)arg0 + 0x40, 0x29);
        temp_v0_2 = func_8004B404(0x48);
        var_s1 = temp_v0_2 != 0;
        *(s32 *)((s8 *)arg0 + 0x20) = temp_v0_2;
    }
    return var_s1;
}
