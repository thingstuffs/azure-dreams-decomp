#include "common.h"

extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099734();
extern s32 func_800A5720();
extern s8 D_8017646B[9];

void func_80175E14(s32 arg0) {
    register s32 call_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 pass_value ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register s32 saved_value ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    s32 result;

    result = func_800990FC();
    call_arg = arg0;
    pass_value = result;
    saved_value = pass_value;
    func_80099290(func_80099194(D_8017646B, func_80099734(call_arg, pass_value)));
    func_800A5720(saved_value);
}
