#include "common.h"

extern s32 func_8008C0AC();

void func_8008C0F0(s16 arg0, s16 arg1) {
    s32 x;
    s32 y;

    x = (s16)arg0;
    if (x < 0) {
        x += 0x3F;
    }
    y = (s16)arg1;
    x >>= 6;
    if (y < 0) {
        y += 0x3F;
    }
    func_8008C0AC(x, y >> 6);
}
