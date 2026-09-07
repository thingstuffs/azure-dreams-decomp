#include "common.h"

void func_80096A90(s32 *arg0, s16 *arg1) {
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    x = arg1[0] + arg1[2];
    y = arg1[1] + arg1[3];
    x2 = x + arg1[4];
    y2 = y + arg1[5];
    y <<= 16;
    x2 <<= 16;
    y2 <<= 16;
    x = (x << 16) + 0x1FFFFF;
    y += 0x1FFFFF;
    x2 += 0xFFE00000;
    y2 += 0xFFEC0000;
    if (x < arg0[0]) {
        arg0[0] = x;
    }
    if (y < arg0[2]) {
        arg0[2] = y;
    }
    if (arg0[1] < x2) {
        arg0[1] = x2;
    }
    if (arg0[3] < y2) {
        arg0[3] = y2;
    }
}
