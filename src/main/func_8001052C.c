#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004DA74();           /* extern */
extern s32 D_800282BC;
__asm__(".set D_800282BC, 0x800282BC");

void func_8002352C(s32 arg0) {
    s32 *var_s1;
    s32 temp_a0;
    s32 temp_a1;
    s32 var_s0;
    s32 var_s2;

    var_s2 = 0;
    var_s1 = &D_800282BC;
    var_s0 = 0x90;
    do {
        temp_a1 = *var_s1;
        var_s1 += 1;
        temp_a0 = arg0 + var_s0;
        var_s0 += 0x48;
        var_s2 += 1;
        func_8004DA74(temp_a0, temp_a1, 1);
    } while (var_s2 < 3);
}
