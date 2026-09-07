#include "common.h"

extern void func_800AD4D0(void *arg);

void func_800AA754(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u8 value;

    (void)arg0;
    (void)arg1;
    (void)arg2;
    func_800AD4D0(arg3);
    value = arg3[0x29];
    if (value < arg3[0x28]) {
        arg3[0x28] = value;
    }
}
