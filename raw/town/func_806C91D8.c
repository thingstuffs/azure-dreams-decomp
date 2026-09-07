#include "common.h"

extern s32 func_8001762C(void);
extern s32 func_80016A78();
extern s32 func_80016B20();

void func_806C91D8(s32 arg0, s32 arg1) {
    if (func_8001762C() >= 5) {
        func_80016A78();
    }
    func_80016B20(arg0, arg1);
}
