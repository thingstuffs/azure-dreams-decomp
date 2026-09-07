#include "common.h"

extern s32 func_800175D0(void);
extern s32 func_80016A1C();
extern s32 func_80016AC4();

void func_806CD298(s32 arg0, s32 arg1) {
    if (func_800175D0() >= 30) {
        func_80016A1C();
    }
    func_80016AC4(arg0, arg1);
}
