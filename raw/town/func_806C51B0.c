#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;
extern s32 D_800190C0[3];

void func_806C51B0(void) {
    s32 *command;
    s32 value;

    D_800190C0[0] = M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x1C), s32 *, 4) << 16;
    value = M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x1C), s32 *, 8);
    do { command = D_800190C0; } while (0);
    command[2] = 0;
    command[1] = value << 16;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x208)(0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x228)(0);
}
