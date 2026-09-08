#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(void *arg0, s32 arg1);
extern void func_80099290(s32 arg0);
extern s32 func_80099368(void *arg0, s32 arg1);
extern s32 func_80099734(s32 arg0, s32 arg1);
extern s32 func_800999B0(s32 arg0);
extern void func_800A5720(s32 arg0);
extern u8 D_80089000[];
extern u8 D_800E0A1B[];

void func_800A6480(s32 arg0, void *arg1) {
    register void *call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 pass_value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 saved_value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result;

    result = func_800990FC();
    call_arg = arg1;
    pass_value = result;
    saved_value = pass_value;
    func_80099290(func_800999B0(func_80099194(D_80089000,
        func_80099734(arg0, func_80099194(D_800E0A1B,
            func_80099368(call_arg, pass_value))))));
    func_800A5720(saved_value);
}
