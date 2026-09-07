#include "common.h"

typedef s32 M2C_UNK;

extern void func_800C2E84(void *arg0, M2C_UNK arg1, M2C_UNK arg2);
extern void func_800C41D4(void *arg0, M2C_UNK arg1, M2C_UNK arg2);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800C4174(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x80), s32 *, 4));
    func_800C41D4(arg0, arg1, arg2);
}
