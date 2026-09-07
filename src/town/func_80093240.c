#include "common.h"

extern u8 D_80083160[];
extern s32 func_800909F8(void *);

s32 func_800909A0(void) {
    s16 *base = (s16 *)D_80083160;
    s16 signedValue = base[0x64];
    u16 value = ((u16 *)base)[0x64];

    if (signedValue != 0) {
        if (signedValue > 0) {
            value -= 0x10;
            base[0x64] = value;
            if ((s16)value < 0) {
                base[0x64] = 0;
                return func_800909F8(base);
            }
        } else if (signedValue < 0) {
            value += 0x10;
            base[0x64] = value;
            if ((s16)value > 0) {
                base[0x64] = 0;
            }
        }
    }

    return base[0x64];
}
