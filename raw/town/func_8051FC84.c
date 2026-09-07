#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80018A64();
extern void *D_80016000;
extern void *D_800190E0;

void func_8051FC84(void) {
    func_80018A64(0x5C8);
    M2C_FIELD(((M2C_FIELD(D_80016000, s32 *, 8) * 8) + M2C_FIELD(D_80016000, s32 *, 0x40)), s8 *, 1) = 2;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), void **, 0x218), M2C_UNK (*)(M2C_UNK *), 0)(&D_800190E0);
}
