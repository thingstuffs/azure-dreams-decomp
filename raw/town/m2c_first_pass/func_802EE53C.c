#include "common.h"
#include "m2c_compat.h"

void func_8040553C(void *arg0) {
    s32 temp_s1;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_a1_4;

    temp_s1 = arg0 + 4;
    (M2C_UNK (*)(s32, M2C_UNK, M2C_UNK))0x80404DEC(temp_s1, 0xF8, 0x48);
    temp_a1 = M2C_FIELD(arg0, void **, 0xB14);
    M2C_FIELD(M2C_FIELD(temp_a1, void **, 4), s16 *, 8) = 0xA0;
    M2C_FIELD(M2C_FIELD(temp_a1, void **, 4), s16 *, 0xA) = 0xB0;
    M2C_FIELD(temp_a1, s32 *, 0) = temp_s1;
    temp_a1_2 = M2C_FIELD(arg0, void **, 0xB08);
    M2C_FIELD(M2C_FIELD(temp_a1_2, void **, 4), s16 *, 8) = 0x60;
    M2C_FIELD(M2C_FIELD(temp_a1_2, void **, 4), s16 *, 0xA) = 0x88;
    M2C_FIELD(temp_a1_2, s32 *, 0) = 0x800841DC;
    temp_a1_3 = M2C_FIELD(arg0, void **, 0xB0C);
    M2C_FIELD(M2C_FIELD(temp_a1_3, void **, 4), s16 *, 8) = 0xD0;
    M2C_FIELD(M2C_FIELD(temp_a1_3, void **, 4), s16 *, 0xA) = 0x88;
    M2C_FIELD(temp_a1_3, s32 *, 0) = 0x8008423C;
    temp_a1_4 = M2C_FIELD(arg0, void **, 0xB10);
    M2C_FIELD(M2C_FIELD(temp_a1_4, void **, 4), s16 *, 8) = 0x20;
    M2C_FIELD(M2C_FIELD(temp_a1_4, void **, 4), s16 *, 0xA) = 0x88;
    M2C_FIELD(temp_a1_4, s32 *, 0) = 0x8008429C;
}
