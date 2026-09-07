#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8();
extern s32 func_80064584();
extern s16 func_8009A8B0();
extern M2C_UNK D_8009A81C;

void func_8009A724(void *arg0, void *arg1) {
    s16 temp_s0;
    s16 temp_s0_2;
    s16 temp_v1;

    temp_s0 = M2C_FIELD(arg0, u16 *, 0x36) - (func_800644B8(M2C_FIELD(arg0, s16 *, 0x10) - 0x80) / 48);
    temp_s0_2 = M2C_FIELD(arg0, u16 *, 0x38) - (func_80064584(M2C_FIELD(arg0, s16 *, 0x10) - 0x80) / 48);
    temp_v1 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) temp_v1;
    M2C_FIELD(arg1, s16 *, 2) = func_8009A8B0(temp_v1, M2C_FIELD(arg1, s16 *, 2), temp_s0);
    M2C_FIELD(arg1, s16 *, 6) = func_8009A8B0((s16) M2C_FIELD(arg0, u16 *, 0xA), M2C_FIELD(arg1, s16 *, 6), temp_s0_2);
    if ((s16) M2C_FIELD(arg0, u16 *, 0xA) <= 0) {
        M2C_FIELD(arg0, u16 *, 0xA) = 0x10U;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_8009A81C;
    }
}
