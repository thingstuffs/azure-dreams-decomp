#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8008F074();
extern M2C_UNK D_800C26C0[3];
extern M2C_UNK D_800D4F88[3];

void func_800C2664(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, s16 *, 0x8C) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0x40;
    func_8008F074(arg0, arg1, *(M2C_FIELD(arg0, u8 *, 0x94) + D_800D4F88));
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = D_800C26C0;
}
