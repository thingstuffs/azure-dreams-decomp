#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_800C2CB0();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A7DF8;
extern M2C_UNK D_800F8F68;

void func_800A7C98(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800A7DF8;
    M2C_FIELD(arg0, M2C_UNK *, 0x50) = 0;
    func_800C2CB0(arg0, arg2, &D_800F8F68, 0);
    func_80033CD8(arg0, &D_80045340);
}
