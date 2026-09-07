#include "common.h"

extern s32 func_8009D218(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void func_80099844(s32, void *);
extern u8 D_800E1D01[9];

/* Checks the target using a scaled low-byte value and conditionally applies D_800E1D01. */
void func_800262B8(s32 target, s32 value) {
    register s32 pinnedValue ASM_REG("$16") = value;
    if (func_8009D218(target, 2) == 0) {
        register s32 scaledLowByte ASM_REG("$6") = (u32)(pinnedValue & 0xFF) >> 2;
        if ((func_800A48F0(target, 0x16, scaledLowByte + 4) << 16) != 0) {
            func_80099844(target, D_800E1D01);
        }
    }
}
