#include "common.h"
extern u8 D_800E3D7C[128];
void func_80017018(void) {
    s32 var_v1;
    s32 base;
    var_v1 = 6;
    base = (s32)&D_800E3D7C[0x24];
    do {
        *(u8*)(var_v1 + base) = 0;
        var_v1 -= 1;
    } while (var_v1 >= 0);
}
