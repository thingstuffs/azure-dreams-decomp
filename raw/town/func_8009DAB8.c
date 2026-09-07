#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_8009BFD8();
M2C_UNK func_8009B29C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009B148;
extern M2C_UNK D_8009B2BC;

void func_8009B218(void *arg0, M2C_UNK arg1, void *arg2, s32 arg3) {
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_8009B148;
    func_80033CD8(arg0, &D_80045340);
    M2C_FIELD(arg0, s16 *, 0x8C) = 0;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0;
    M2C_FIELD(arg2, s32 *, 0) = 0;
    M2C_FIELD(arg2, s8 *, 4) = 0;
    M2C_FIELD(arg2, s8 *, 5) = 0;
    if (arg3 != 0) {
        M2C_FIELD(arg0, s32 *, 0x58) = arg3;
        func_8009BFD8(arg0, arg0, arg1, arg2);
        func_8009B29C();
        return;
    }
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_8009B2BC;
}
