#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80016A38();
M2C_UNK func_80016948();
extern void *D_80016000;
extern M2C_UNK D_80019440;
extern s32 D_80019540;

void func_804803D8(void) {
    func_80016948(&D_80019440, 0x100);
    func_80016A38(&D_80019440);
    D_80019540 = M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), s32 (**)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *), 0x68)(0, 1, 2, &D_80019440);
}
