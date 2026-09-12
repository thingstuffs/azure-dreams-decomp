#include "common.h"

extern s32 func_8009D218(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void func_80099844(s32, void *);
extern u8 D_800E1CD5[9];

/* Conditionally applies D_800E1CD5 using a check indexed by the supplied value's low byte. */
void func_80025760(s32 target, s32 packedValue) {
    u8 savedPackedValue = packedValue;
    if (func_8009D218(target, 1) == 0) {
        register s32 valueGroupIndex ASM_REG("$6") = (u32)(savedPackedValue & 0xFF) >> 2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if ((func_800A48F0(target, 0x15, valueGroupIndex + 2) << 16) != 0) {
            func_80099844(target, D_800E1CD5);
        }
    }
}
