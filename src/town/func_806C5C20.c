#include "common.h"

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* If flag 0xFB1 is set, set flag 0xFD3 and return 1; otherwise clear flags 0xFCB and 0xFCD and return 0. */
s32 func_80016C20(void)
{
    if (func_80018D6C(0xFB1) != 0) {
        func_80018C74(0xFD3);
        return 1;
    }
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
