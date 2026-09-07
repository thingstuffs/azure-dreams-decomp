#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern M2C_UNK func_800A4B94();
extern M2C_UNK func_800A4CD8();
extern M2C_UNK D_800A4B94;

void func_800A4C10(void *arg0) {
    s32 temp_v0;
    void *temp_v1;

    temp_v1 = FIELD(arg0, void *, 0);
    if (temp_v1 != FIELD(arg0, void *, 4)) {
        FIELD(arg0, s32, 0x20) = 9;
        FIELD(arg0, s32, 0x14) = 0;
        FIELD(arg0, s32, 0x18) = 0;
        FIELD(arg0, s32, 0x1C) = 0;
        FIELD(arg0, void *, 4) = temp_v1;
        func_800A4B94(arg0);
        func_800A4CD8();
        return;
    }
    FIELD(arg0, s32, 8) +=
        (FIELD(temp_v1, s32, 0) - FIELD(arg0, s32, 8)) /
        FIELD(arg0, s32, 0x20);
    FIELD(arg0, s32, 0xC) +=
        (FIELD(FIELD(arg0, void *, 0), s32, 4) - FIELD(arg0, s32, 0xC)) /
        FIELD(arg0, s32, 0x20);
    FIELD(arg0, s32, 0x10) +=
        (FIELD(FIELD(arg0, void *, 0), s32, 8) - FIELD(arg0, s32, 0x10)) /
        FIELD(arg0, s32, 0x20);
    temp_v0 = FIELD(arg0, s32, 0x20) - 1;
    FIELD(arg0, s32, 0x20) = temp_v0;
    if (temp_v0 <= 0) {
        FIELD(arg0, M2C_UNK *, 0x28) = &D_800A4B94;
    }
}
