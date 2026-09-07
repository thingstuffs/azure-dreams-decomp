#include "common.h"

extern s32 func_80176F2C(void *arg0);
extern s32 func_80176F10(void);
extern s32 func_80177E6C(s32 arg0, void *arg1);
extern s32 func_80063734(s32 arg0);

s32 func_80040690(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    var_s0 = 0x800000;
    while (1) {
        temp_v0 = func_80176F2C(arg0);
        if (temp_v0 != 0) {
            break;
        }
        if (--var_s0 == 0) {
            return (func_80176F10(), 0);
        }
    }
    if (temp_v0 > 0) {
        return 0;
    }
    temp_v0_2 = *((s32 *)arg0 + 2) == 0;
    *((s32 *)arg0 + 2) = temp_v0_2;
    func_80177E6C(temp_v0, *((void **)arg0 + temp_v0_2));
    func_80063734(temp_v0);
    return (func_80176F10(), 1);
}
