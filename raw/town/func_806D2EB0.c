#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800161EC();
M2C_UNK func_80016D78();

void func_800166B0(s32 arg0, void *arg1, M2C_UNK arg2) {
    func_80016D78(M2C_FIELD(((M2C_FIELD(((func_800161EC(arg0, arg2) * 8) + arg0), s16 *, 2) * 4) + M2C_FIELD(arg1, s32 *, 0x14)), s16 *, 2));
}
