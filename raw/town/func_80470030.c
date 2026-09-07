#include "common.h"

extern void func_80017074(void) __attribute__((noreturn));
extern void func_80019618(s32, s32);
extern void func_80019928(s32, s32);
extern s32 func_8001A510(s32);

s32 func_80017030(s32 arg0, s32 arg1) {
    if (func_8001A510(0x798) != 0) {
        func_80019928(arg0, arg1);
        func_80017074();
    }
    func_80019618(arg0, arg1);
    return 1;
}
