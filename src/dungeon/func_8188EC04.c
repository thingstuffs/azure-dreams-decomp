#include "common.h"

extern s32 func_8009D218(s32, s32);
extern s32 func_800A48F0(s32, s32, s32);
extern void func_80099844(s32, void *);
extern u8 D_800E1D28[9];

/* Conditionally apply D_800E1D28 to the target after checking a scaled low-byte value. */
void func_80026404(s32 target, s32 packedValue) {
    u8 savedPackedValue = packedValue;
    if (func_8009D218(target, 4) == 0) {
        u32 lowByteQuarter = savedPackedValue;
        lowByteQuarter >>= 2;
        if ((func_800A48F0(target, 0x17, lowByteQuarter + 2) << 16) != 0) {
            func_80099844(target, D_800E1D28);
        }
    }
}
