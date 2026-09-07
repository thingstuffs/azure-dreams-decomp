#include "common.h"

extern s16 D_80083228[5];

u32 func_800C2D0C(s32 arg0) {
    s32 value;

    arg0 -= 0x600;
    value = (D_80083228[0] - arg0) & 0xFFF;
    if (value < 0) {
        value += 0x3FF;
    }
    return (u32)value >> 10;
}
