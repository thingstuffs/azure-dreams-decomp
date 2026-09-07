#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033CD8();
extern s16 func_800374F4();
extern M2C_UNK func_800A8BBC();
extern M2C_UNK D_800A9528[3];
extern M2C_UNK D_800A9624[3];
extern M2C_UNK D_800A970C[3];

void func_800A957C(void *arg0, void *arg1, void *arg2) {
    *(M2C_UNK **)((s8 *)arg0 - 0x10) = D_800A9624;
    *(M2C_UNK **)((s8 *)arg0 + 0x50) = D_800A970C;
    *(s16 *)((s8 *)arg2 + 0x1C) = 0x37;
    *(s16 *)((s8 *)arg2 + 0x1E) = 0x37;
    *(u16 *)((s8 *)arg2 + 0x20) = 0xFF00;
    *(s16 *)((s8 *)arg1 + 0x0E) = func_800374F4(0xFFFF);
    *(s16 *)((s8 *)arg1 + 0x12) = func_800374F4(0xFFFF);
    *(s16 *)((s8 *)arg1 + 0x16) = func_800374F4(0xFFFF);
    func_80033CD8(arg0, D_800A9528);
    func_800A8BBC(0x10, 0x11, 0x12, 0x13, arg1);
}
