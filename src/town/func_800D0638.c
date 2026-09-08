#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_800374F4();
extern M2C_UNK func_800C2E84();
extern M2C_UNK D_800CD650;
extern M2C_UNK D_800D7284;

// Initializes an object with shared data and a generated value scaled in units of 21.
void func_800CDD98(void *object, M2C_UNK unusedArg, M2C_UNK initValue) {
    func_800C2E84(object, initValue, &D_800D7284);
    *(M2C_UNK **)((u8 *)object + 0x50) = &D_800CD650;
    *(s16 *)((u8 *)object + 0x6C) = (s16)(((func_800374F4(4) & 0xFFFF) * 0x15) + 0x15);
}
