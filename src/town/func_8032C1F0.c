#include "common.h"

extern void func_80019B54(s32 arg0, s32 arg1);
extern void func_80019BC0(void);
extern s32 func_8001B0C8(void);

void func_800169F0(s32 arg0, s32 arg1) {
    if (func_8001B0C8() >= 0x19) {
        func_80019BC0();
    }
    func_80019B54(arg0, arg1);
}
