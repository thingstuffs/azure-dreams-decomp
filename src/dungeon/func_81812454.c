#include "common.h"

extern void func_80027328();
extern void func_80027384();
extern void func_800273E4();
extern void func_80027498(void) __attribute__((noreturn));

void func_80027454(s32 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg1 == 0) {
        func_80027328(arg0, arg2);
        func_80027498();
        return;
    }
    if (*arg0 != 0x13) {
        func_80027384(arg0, arg2);
        func_80027498();
        return;
    }
    func_800273E4(arg0, arg2, arg3);
}
