#include "common.h"

extern u32 *D_801131EC[3];
extern s32 func_8008AFA8(void);

s32 func_8008AF2C(s32 arg0, s32 arg1, s32 arg2) {
    volatile u32 *flags;
    volatile u32 *value;
    u32 bits;
    u32 mask1;
    u32 mask2;

    flags = D_801131EC[0];
    if (flags[1] != 0) {
        mask1 = 0x3F000000;
        mask2 = 0x007F0000;
        value = flags + 1;
        do {
            bits = *flags;
            if (arg0 == ((bits >> 23) & 1) &&
                arg1 == ((bits & mask1) >> 24) &&
                arg2 == ((bits & mask2) >> 16)) {
                (void)*value;
                return func_8008AFA8();
            }

            value += 2;
            flags += 2;
        } while (*value != 0);
    }

    return 0;
}
