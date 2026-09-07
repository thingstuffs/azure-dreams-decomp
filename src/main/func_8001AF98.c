#include "common.h"

extern void func_8007C040(s32 *arg0, s32 *arg1, s32 arg2);

extern s32 D_80400114[];
extern s32 D_80400120[];

void func_8001AF98(void *arg0) {
    s32 *var_a1;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;

    var_a2 = 0;
    var_a1 = (s32 *)((u8 *)arg0 + 0x208);
    var_v1 = 0x1781;
    do {
        temp_v0 = *var_a1;
        var_a1 += 1;
        var_v1 -= 1;
        var_a2 ^= temp_v0;
    } while (var_v1 >= 0);
    *(s32 *)((u8 *)arg0 + 0x204) = var_a2;
    func_8007C040(D_80400114, D_80400120, var_a2);
}
