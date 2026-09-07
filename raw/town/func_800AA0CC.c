#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800A790C();
M2C_UNK func_800C2CB0();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A78AC;
extern M2C_UNK D_800F842C;

void func_800A782C(void *arg0, void *arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800A78AC;
    func_800C2CB0(arg0, arg2, &D_800F842C, 0);
    func_80033CD8(arg0, &D_80045340);
    M2C_FIELD(arg1, s16 *, 0xA) = 0;
    func_800A790C(arg0, arg1, arg2);
}
