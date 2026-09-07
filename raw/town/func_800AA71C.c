#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_800A7EC0;

void func_800A7E7C(void *arg0, M2C_UNK arg1, void *arg2) {
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800A7EC0;
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) M2C_FIELD(arg0, u8 *, 0x96);
    M2C_FIELD(arg2, M2C_UNK **, 8) = &D_8006E240;
    func_80033CD8(arg0, &D_80045340);
}
