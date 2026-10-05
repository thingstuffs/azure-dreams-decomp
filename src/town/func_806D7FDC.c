#include "common.h"

extern s32 func_800187FC(void);
extern s32 func_800178D0(void);
extern s32 func_80017978(s32 first_value, s32 second_value);

void func_800167DC(s32 first_value, s32 second_value, s32 unused_value) {
    if (func_800187FC() >= 40) {
        func_800178D0();
    }
    func_80017978(first_value, second_value);
}
