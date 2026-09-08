#include "common.h"

extern s32 func_8009D218(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void func_80099844(s32, void *);
extern u8 D_800E1D28[9];

/* Conditionally apply D_800E1D28 to the target after checking a scaled low-byte value. */
void func_80026404(s32 target, s32 packedValue) {
    register s32 savedPackedValue ASM_REG("$16") = packedValue;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if (func_8009D218(target, 4) == 0) {
        register s32 lowByteQuarter ASM_REG("$6") = (u32)(savedPackedValue & 0xFF) >> 2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if ((func_800A48F0(target, 0x17, lowByteQuarter + 2) << 16) != 0) {
            func_80099844(target, D_800E1D28);
        }
    }
}
