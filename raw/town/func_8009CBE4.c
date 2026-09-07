#include "common.h"

typedef s32 M2C_UNK;

extern void func_80094984(M2C_UNK arg0, void *arg1, M2C_UNK arg2);
extern void func_8009A1E8(void *arg0, M2C_UNK arg1, M2C_UNK arg2);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_8009A344(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80094984(M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s32 *, 0x24), arg0, arg2);
    func_8009A1E8(arg0, arg1, arg2);
}
