#include "common.h"

extern s16 D_80083228;

u32 func_80095360(s32 arg0) {
    s32 value;

    arg0 -= 0x500;
    value = (D_80083228 - arg0) & 0xFFF;
    if (value < 0) {
        value += 0x1FF;
    }
    return (u32)value >> 9;
}
