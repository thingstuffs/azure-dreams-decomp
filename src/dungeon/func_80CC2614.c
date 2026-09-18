#include "common.h"

extern s32 func_800990FC(s32, s32, s32, s32);
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099734();
extern s32 func_800A5720();
extern s8 D_8017646B[9];

void func_80175E14(s32 source_value, s32 input_value, s32 input_value_2, s32 input_value_3) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    adjusted_value = func_80099734(source_value, current_value = func_800990FC(source_value, input_value, input_value_2, input_value_3));
    original_value = current_value;
    current_value = adjusted_value;
    func_80099290(func_80099194(D_8017646B, current_value));
    func_800A5720(original_value);
}
