#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80091950(void);

void func_80091934(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    FIELD(arg0, s8 *, 0x9A) = 0x2B;
    if (arg3 == 0) {
        FIELD(arg0, s8 *, 0x9B) = 0x10;
        return func_80091950();
    }
    FIELD(arg0, s8 *, 0x9B) = 0;
    FIELD(arg0, s32 *, 0x8C) = 0;
    return;
}
