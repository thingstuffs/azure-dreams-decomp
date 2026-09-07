#include "common.h"

extern s32 D_80408C8C;
__asm__(".set D_80408C8C, 0x80408C8C");

extern void func_80051B50(s32 arg0, s32 arg1, s32 arg2);

void func_8001C7F4(s32 arg0) {
    s32 *var_s1;
    s32 var_s0;
    s32 var_s2;

    var_s2 = 0;
    var_s1 = &D_80408C8C;
    var_s0 = 0x90;
    do {
        func_80051B50(arg0 + var_s0, *var_s1, 1);
        var_s1++;
        var_s0 += 0x3C;
        var_s2++;
    } while (var_s2 < 4);
}
