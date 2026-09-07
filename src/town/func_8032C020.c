#include "common.h"

extern s32 func_8001B0C8(void);
extern s32 func_80019BC0();
extern s32 func_80019B54();

void func_80016820(s32 arg0, s32 arg1) {
    if (func_8001B0C8() >= 10) {
        func_80019BC0();
    }
    func_80019B54(arg0, arg1);
}
