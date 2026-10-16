#include "common.h"
#include "m2c_compat.h"

extern s32 D_8001B320;
extern s32 D_8001B324;

void func_8001A0BC(void) {
    void *temp_a0;
    void *temp_a2;

    temp_a2 = *(void **)0x80016000;
    temp_a0 = (M2C_FIELD(temp_a2, s32 *, 0x14) * 0x1C) + D_8001B320;
    D_8001B324 = M2C_FIELD(temp_a2, s32 *, 0);
    M2C_FIELD(((M2C_FIELD(temp_a0, u8 *, 0) * 0x10) + M2C_FIELD(temp_a0, s32 *, 0x10)), M2C_UNK (**)(void *, u8, s32), 4)(temp_a0, M2C_FIELD(temp_a0, u8 *, 0), M2C_FIELD(temp_a2, s32 *, 0));
}
