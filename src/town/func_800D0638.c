#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_800374F4();
extern M2C_UNK func_800C2E84();
extern M2C_UNK D_800CD650;
extern M2C_UNK D_800D7284;

void func_800CDD98(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D7284);
    *(M2C_UNK **)((u8 *)arg0 + 0x50) = &D_800CD650;
    *(s16 *)((u8 *)arg0 + 0x6C) = (s16)(((func_800374F4(4) & 0xFFFF) * 0x15) + 0x15);
}
