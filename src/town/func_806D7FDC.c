#include "common.h"

extern s32 func_800187FC(void);
extern s32 func_800178D0(void);
extern s32 func_80017978(s32 arg0, s32 arg1);

void func_800167DC(s32 arg0, s32 arg1, s32 arg2) {
    if (func_800187FC() >= 40) {
        func_800178D0();
    }
    func_80017978(arg0, arg1);
}
