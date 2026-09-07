#include "common.h"

extern u8 D_80016000[0x10];

extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);

s32 func_800173F0(void) {
    s32 var_v0;

    if (func_80018B5C(0x5C8) != 0) {
        {
            void *v0;
            u8 *v1;

            v0 = *(void **)D_80016000;
            v1 = (u8 *)((*(s32 *)((u8 *)v0 + 8) << 3) + *(s32 *)((u8 *)v0 + 0x40));
            v1[1] -= 1;
        }
        var_v0 = 0;
        {
            void *v1;
            u8 *v0;

            v1 = *(void **)D_80016000;
            v0 = (u8 *)((*(s32 *)((u8 *)v1 + 8) << 3) + *(s32 *)((u8 *)v1 + 0x40));
            
            if (v0[1] == 0) {
                func_80018ADC(0x5C8);
            }
        }
        return var_v0;
    }
    var_v0 = func_80018B5C(0x11FC) != 0;
    return var_v0;
}
