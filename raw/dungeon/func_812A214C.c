#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009900C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800991C0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A17D4(s32, u8, u8);                 /* extern */
extern M2C_UNK D_80081490;
extern void *D_8014F710;

void func_8014E94C(s32 arg0) {
    s16 sp10;
    s16 sp12;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s32 temp_s2;
    void *temp_a0;
    void *temp_s0;
    void *temp_s1;

    sp10 = 1;
    sp12 = -1;
    temp_s1 = D_8014F710 + 0x20;
    temp_s0 = M2C_FIELD(D_8014F710, void **, 0xC);
    temp_s2 = M2C_FIELD(D_8014F710, s32 *, 8);
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) & 0xFF7F);
    var_a2 = 0x3000;
    if (M2C_FIELD(temp_s1, s32 *, 0x1C) & 0x2000) {
        var_a2 = 0x300;
    }
    func_800991C0(M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25), var_a2);
    temp_a0 = &sp10 + (arg0 * 4);
    M2C_FIELD(temp_s0, u8 *, 0x24) = (u8) (M2C_FIELD(&D_80081490, u8 *, 0x24) + M2C_FIELD(temp_a0, u8 *, 0));
    M2C_FIELD(temp_s0, u8 *, 0x25) = (u8) (M2C_FIELD(&D_80081490, u8 *, 0x25) + M2C_FIELD(temp_a0, u8 *, 2));
    func_800A17D4(temp_s2, M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25));
    var_a2_2 = 0x3000;
    if (M2C_FIELD(temp_s1, s32 *, 0x1C) & 0x2000) {
        var_a2_2 = 0x300;
    }
    func_8009900C(M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25), var_a2_2);
}
