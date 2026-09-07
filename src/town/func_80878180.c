#include "common.h"

extern u8 D_80701E2C[];
extern void func_80702670(s32);

void func_80702180(s32 arg0, s32 arg1) {
    s32 offset;

    offset = (arg1 * 8) + (arg0 << 5);
    if (*(s32 *) &D_80701E2C[offset] & 1) {
        func_80702670(0x1F9);
    }
}
