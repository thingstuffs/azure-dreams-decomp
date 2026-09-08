#include "common.h"

extern s32 func_80018C74(s32);
extern s32 func_80018CEC(s32);
extern s32 func_80018D6C(s32);

// Updates event flags based on three prerequisite checks and reports whether they passed.
s32 func_800167B4(void)
{
    if (func_80018D6C(0x7D1) != 0 &&
        func_80018D6C(0x7D2) == 0 &&
        func_80018D6C(0xFCF) != 0) {
        func_80018C74(0x7D8);
        return 1;
    }

    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
