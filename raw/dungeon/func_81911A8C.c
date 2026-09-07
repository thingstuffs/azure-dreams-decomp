#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8006658C();
M2C_UNK func_800667A8();
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;

void func_81911A8C(void *arg0, void *arg1, void *arg2) {
    s8 temp_v0;
    s8 temp_v0_2;
    void *temp_s0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    temp_s0 = M2C_FIELD(M2C_FIELD(&D_80083160, void **, 0), void **, 0x8D0);
    M2C_FIELD(M2C_FIELD(&D_80083160, void **, 0), void **, 0x8D0) = (void *) (temp_s0 + 0x10);
    M2C_FIELD(temp_s0, s16 *, 0xC) = 0x140;
    M2C_FIELD(temp_s0, s16 *, 0xE) = 0xE0;
    M2C_FIELD(temp_s0, s16 *, 8) = 0;
    M2C_FIELD(temp_s0, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s0, u8 *, 4) = 0xC0;
    temp_v0 = -0x40 - (M2C_FIELD(arg2, s8 *, 5) * 0xC);
    M2C_FIELD(temp_s0, s8 *, 6) = temp_v0;
    M2C_FIELD(temp_s0, s8 *, 5) = temp_v0;
    func_800667A8(temp_s0);
    M2C_FIELD(temp_s0, u8 *, 7) = (u8) (M2C_FIELD(temp_s0, u8 *, 7) | 2);
    func_8006658C(M2C_FIELD(&D_80083160, s32 *, 0) + 0xB0, temp_s0);
    temp_v0_2 = (u8) M2C_FIELD(arg2, s8 *, 5) - 1;
    M2C_FIELD(arg2, s8 *, 5) = temp_v0_2;
    if ((temp_v0_2 << 0x18) == 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
