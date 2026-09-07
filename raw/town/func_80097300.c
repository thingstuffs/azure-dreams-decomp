#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80094A38();

void func_80094A60(s32 *arg0, void *arg1) {
    s32 value = arg0[M2C_FIELD(arg1, s16 *, 0x16)];
    if (value != 0) {
        func_80094A38(value);
    }
}
