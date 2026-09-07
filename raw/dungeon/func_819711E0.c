#include "common.h"

extern s16 D_80025FF4;
extern s32 D_800814A0[3];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_819711E0(void *arg0, void *arg1, void *arg2) {
    s32 value;
    u16 count;
    void *src;

    count = FIELD(arg0, u16, 0x38) - 1;
    value = (s32) ((s32) (count << 16) >> 9) / (s16) FIELD(arg0, s16, 0x3A);
    D_80025FF4 = 1;
    FIELD(arg0, u16, 0x38) = count;
    FIELD(arg2, s8, 0xE) = (s8) value;
    FIELD(arg2, s8, 0xD) = (s8) value;
    FIELD(arg2, s8, 0xC) = (s8) value;

    src = FIELD(arg0, void *, 0x40);
    FIELD(arg1, u16, 2) = FIELD(arg0, u16, 0x44);
    FIELD(arg1, u16, 6) = FIELD(arg0, u16, 0x46);
    FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x48);
    FIELD(arg1, u16, 2) = (u16) (FIELD(arg1, u16, 2) + FIELD(src, u16, 2));
    FIELD(arg1, u16, 6) = (u16) (FIELD(arg1, u16, 6) + FIELD(src, u16, 6));
    FIELD(arg1, u16, 0xA) = (u16) (FIELD(arg1, u16, 0xA) + FIELD(src, u16, 0xA));

    if (FIELD(arg0, s16, 0x38) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
