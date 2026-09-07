#include "common.h"

extern void func_8004E99C(s32);

void func_80028534(void *arg0) {
    s32 **var_s0;
    s32 var_s1;

    var_s1 = 6;
    var_s0 = arg0 + 0x18;
    do {
        var_s1 += 1;
        func_8004E99C(**var_s0);
        **var_s0 = 0;
        var_s0 += 1;
    } while (var_s1 < 0xE);
    func_8004E99C(**(s32 **)((u8 *)arg0 + 0x38));
}
