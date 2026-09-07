#include "common.h"

extern s16 D_8008146C;
extern u8 D_80082E6A;

s32 func_8003E14C(void)
{
    if (D_80082E6A == 2) {
        s32 result = 0x28;
        s32 current = D_8008146C;

        if (current < 0x29) {
            result = current;
        }
        return result;
    }
    return 0;
}
