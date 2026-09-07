#include "common.h"
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80083160[];
extern M2C_UNK func_8006658C();
extern M2C_UNK func_80066640();
extern M2C_UNK func_800666E0();
extern M2C_UNK func_80067F20();

s32 func_800A5FC0(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    void *temp_s0;
    void *temp_s2;
    void *temp_v1;
    void **temp_s3;

    temp_v1 = D_80083160[0];
    temp_s2 = M2C_FIELD(temp_v1, void **, 0x8D0);
    M2C_FIELD(temp_v1, void **, 0x8D0) = (void *) (temp_s2 + 0xC);
    temp_s0 = M2C_FIELD(M2C_FIELD(&D_80083160, void **, 0), void **, 0x8D0);
    M2C_FIELD(M2C_FIELD(&D_80083160, void **, 0), void **, 0x8D0) = (void *) (temp_s0 + 0x18);
    temp_s3 = (void **)&D_80083160;
    func_80067F20(temp_s2, 0, 0, M2C_FIELD(arg0, s32 *, 4), 0);
    M2C_FIELD(temp_s0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0);
    func_800666E0(temp_s0);
    func_80066640(temp_s0, 1);
    M2C_FIELD(temp_s0, s32 *, 0x10) = 0xE00000;
    M2C_FIELD(temp_s0, s32 *, 8) = 0;
    M2C_FIELD(temp_s0, s16 *, 0xE) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x16) = 0xE0;
    temp_v0 = M2C_FIELD(arg0, u16 *, 8) - 1;
    M2C_FIELD(arg0, u16 *, 8) = temp_v0;
    if ((s16) temp_v0 <= 0)
        goto zero_case;
    {
        s32 delta = 0x140 - M2C_FIELD(arg0, s16 *, 0xA);
        M2C_FIELD(arg0, s16 *, 0xA) = M2C_FIELD(arg0, u16 *, 0xA) + delta / (s16) temp_v0;
    }
    goto common_case;
zero_case:
    M2C_FIELD(arg0, u16 *, 8) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = 0x140;
common_case:
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0xA);
    M2C_FIELD(temp_s0, u16 *, 0x14) = temp_v0_2;
    M2C_FIELD(temp_s0, u16 *, 0xC) = temp_v0_2;
    func_8006658C((u8 *)M2C_FIELD(temp_s3, void **, 0) + ((M2C_FIELD(arg0, s16 *, 0xC) * 4) + 0x70), temp_s0);
    func_8006658C((u8 *)M2C_FIELD(temp_s3, void **, 0) + ((M2C_FIELD(arg0, s16 *, 0xC) * 4) + 0x70), temp_s2);
    return 0;
}
