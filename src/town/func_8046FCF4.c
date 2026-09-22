#include "common.h"

extern void func_800187AC(void);
extern s32 func_80019928(void);

/* Scene step: report busy while the 0x187AC dialogue is still up, else close it. */
s32 func_80016CF4(void) {
    if (func_80019928() != 0) {
        return 1;
    }
    func_800187AC();
    return 0;
}
