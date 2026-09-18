#include "common.h"

extern s32 func_800990FC(s32, void *, s32, s32);
extern s32 func_80099194(void *arg0, s32 arg1);
extern void func_80099290(s32 arg0);
extern s32 func_80099368(void *arg0, s32 arg1);
extern s32 func_80099734(s32 arg0, s32 arg1);
extern s32 func_800999B0(s32 arg0);
extern void func_800A5720(s32 arg0);
extern u8 D_80089000[];
extern u8 D_800E0A1B[];

void func_800A6480(s32 actor, void *item, s32 buffer_arg2, s32 buffer_arg3) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    adjusted_value = func_80099368(item, current_value = func_800990FC(actor, item, buffer_arg2, buffer_arg3));
    original_value = current_value;
    current_value = adjusted_value;
    func_80099290(func_800999B0(func_80099194(D_80089000,
        func_80099734(actor, func_80099194(D_800E0A1B, current_value)))));
    func_800A5720(original_value);
}
