#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C4174();
M2C_UNK func_800C7E58();

void func_800C7DB8(void *arg0, void *arg1) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((s16) temp_v0 <= 0) {
        func_800C4174(arg0);
        M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0x84);
        M2C_FIELD(arg1, s16 *, 6) = (s16) M2C_FIELD(arg0, u16 *, 0x86);
        func_800C7E58();
        return;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 0x84) - (s16) M2C_FIELD(arg1, u16 *, 2)) / (s16) temp_v0));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 0x86) - M2C_FIELD(arg1, s16 *, 6)) / (s16) M2C_FIELD(arg0, u16 *, 0x6C)));
}
