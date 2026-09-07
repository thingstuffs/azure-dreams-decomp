#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800A1080();
extern M2C_UNK func_800A12B4();
extern M2C_UNK D_800A0E3C[3];
extern M2C_UNK D_80100B70[3];

void func_800A0DAC(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    func_800A12B4(&D_80100B70, arg2, arg3);
    M2C_FIELD(arg0, u16 *, 0x6E) = (u16)(M2C_FIELD(arg0, u16 *, 0x6E) + 0x10);
    if (func_800A1080(&D_80100B70, arg2, arg3) != 0) {
        M2C_FIELD(arg0, s16 *, 0x6C) = 0x20;
        M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800A0E3C;
    }
}
