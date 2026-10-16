#include "common.h"

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* Clear flags 0xFCB and 0xFCD; if 0x7D1 and 0xFC6 are set and 0x7D2 is clear, set flag 0x7D5 and return 1. */
s32 func_80016D40(void)
{
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    if ((func_80018D6C(0x7D1) != 0) &&
        (func_80018D6C(0x7D2) == 0) &&
        (func_80018D6C(0xFC6) != 0)) {
        func_80018C74(0x7D5);
        return 1;
    }
    return 0;
}
