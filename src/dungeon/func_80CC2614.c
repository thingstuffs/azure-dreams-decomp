#include "common.h"

extern s32 func_800990FC(s32, s32, s32, s32);
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099734();
extern s32 func_800A5720();
extern s8 D_8017646B[9];

/* Process the inputs, dispatch the table-based result, and finalize the saved value. */
void func_80175E14(s32 source_value, s32 input_value, s32 input_value_2, s32 input_value_3) {
    register s32 call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 pass_value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 saved_value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result;

    result = func_800990FC(source_value, input_value, input_value_2, input_value_3);
    call_arg = source_value;
    pass_value = result;
    saved_value = pass_value;
    func_80099290(func_80099194(D_8017646B, func_80099734(call_arg, pass_value)));
    func_800A5720(saved_value);
}
