#include "common.h"

extern void func_800BA414(void *arg0, s32 arg1, void *arg2, s16 arg3);

s32 func_800BA384(void *arg0, s32 arg1, u8 *arg2) {
    volatile s16 *scratch = (volatile s16 *)0x1F800000;
    register u8 *next ASM_REG("$6");
    register s32 value ASM_REG("$5");
    s32 result;

    scratch[0x46] = 0;
    scratch[0x42] = 0;
    scratch[0x3E] = 0;
    scratch[0x3A] = 0;
    scratch[0x40] = -31;
    scratch[0x38] = -31;
    scratch[0x44] = 31;
    scratch[0x3C] = 31;
    scratch[0x3D] = -31;
    scratch[0x39] = -31;
    scratch[0x45] = 31;
    scratch[0x41] = 31;

    for (;;) {
        func_800BA414(arg0, arg1, arg2, *(s16 *)(arg2 + 6));
        next = *(u8 **)((u8 *)arg0 - 8);
        arg0 = next + 32;
        if (next == 0) {
            break;
        }
        value = *(s32 *)(next + 8);
        next = *(u8 **)(next + 12);
        arg1 = value;
        arg2 = next;
    }
    result = 0;
    return result;
}
