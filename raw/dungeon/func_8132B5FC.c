#include "common.h"

#define FIELD(p, type, off) (*(type *)((s8 *)(p) + (off)))

extern void func_800478B8(void *);
extern s32 D_800814A0[3];

void func_80172DFC(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;

    FIELD(arg0, s32, 0x58) = FIELD(arg0, s32, 0x58) + FIELD(arg0, s32, 0x64);
    FIELD(arg0, s32, 0x5C) = FIELD(arg0, s32, 0x5C) + FIELD(arg0, s32, 0x68);
    FIELD(arg0, s32, 0x60) = FIELD(arg0, s32, 0x60) + FIELD(arg0, s32, 0x6C);
    FIELD(arg1, s32, 0) = FIELD(arg1, s32, 0) + FIELD(arg0, s32, 0x58);
    FIELD(arg1, s32, 4) = FIELD(arg1, s32, 4) + FIELD(arg0, s32, 0x5C);
    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 8) + FIELD(arg0, s32, 0x60);
    temp_v0 = FIELD(arg0, u16, 0x18) + 1;
    FIELD(arg0, u16, 0x18) = temp_v0;
    if (!(temp_v0 & 1)) {
        func_800478B8(arg2);
    }
    FIELD(arg2, u16, 0x1C) = FIELD(arg2, u16, 0x1C) + 0x28;
    FIELD(arg2, u16, 0x1E) = FIELD(arg2, u16, 0x1E) + 0x28;
    temp_v0_2 = FIELD(arg0, u16, 0x16) - 1;
    FIELD(arg0, u16, 0x16) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
