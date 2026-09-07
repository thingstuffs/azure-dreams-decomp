#include "common.h"

extern void func_800187AC(void);
extern s32 func_80019928(void);

s32 func_80016CF4(void) {
    if (func_80019928() != 0) {
        return 1;
    }
    func_800187AC();
    return 0;
}
