#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0[];

void func_818DAE84(void *arg0) {
    s32 count;
    s16 next_count;
    s32 progress;
    void *inner;

    inner = FIELD(arg0, void *, 0);
    FIELD(inner, u16, 0x52) = (u16)(FIELD(inner, u16, 0x52) | 0x8000);

    progress = FIELD(arg0, s32, 0xC);
    if (progress < 0x50) {
        progress += 8;
    }

    count = FIELD(arg0, s16, 0x10);
    FIELD(arg0, s32, 0xC) = progress;
    if (count < 9) {
        FIELD(arg0, s32, 0xC) = count * 8;
    }

    next_count = (u16)FIELD(arg0, s16, 0x10) - 1;
    FIELD(arg0, s16, 0x10) = next_count;
    if ((next_count << 16) <= 0) {
        FIELD(arg0, u16, -2) = (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
