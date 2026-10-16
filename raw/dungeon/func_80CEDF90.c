#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
s32 func_800644B8(s32);                             /* extern */
s32 func_80064584(s32);                             /* extern */
u8 func_80069EF8();                                 /* extern */
extern M2C_UNK D_8016ACEC;
extern M2C_UNK D_8016AE2C;

void func_8016B790(void *arg0, void *arg1) {
    s32 temp_s1_3;
    s32 temp_s2;
    s32 temp_s2_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x18) = 6;
        M2C_FIELD(temp_s0, s16 *, 0x1A) = 6;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016AE2C;
        func_8004491C(temp_v0, &D_8016ACEC);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x50);
        temp_s1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s1_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s1_2, u8 *, 0xC) = func_80069EF8();
        M2C_FIELD(temp_s1_2, u8 *, 0xD) = func_80069EF8();
        M2C_FIELD(temp_s1_2, u8 *, 0xE) = func_80069EF8();
        M2C_FIELD(temp_v0, u8 *, 0x20) = (u8) M2C_FIELD(temp_s1_2, u8 *, 0xC);
        M2C_FIELD(temp_s0, u8 *, 1) = (u8) M2C_FIELD(temp_s1_2, u8 *, 0xD);
        M2C_FIELD(temp_s0, s16 *, 0x60) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x5C) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x58) = 0;
        M2C_FIELD(temp_s0, u8 *, 2) = (u8) M2C_FIELD(temp_s1_2, u8 *, 0xE);
        temp_s2 = func_80069EF8() & 0xFFF;
        temp_s1_3 = (s32) (M2C_FIELD(arg0, s16 *, 0xAE) * func_80064584(temp_s2)) >> 0xC;
        M2C_FIELD(temp_s0, s16 *, 0x62) = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xAE) * func_800644B8(temp_s2)) >> 0xC);
        temp_s2_2 = func_80069EF8() & 0xFFF;
        M2C_FIELD(temp_s0, s16 *, 0x5A) = (s16) ((s32) (temp_s1_3 * func_80064584(temp_s2_2)) >> 0xC);
        M2C_FIELD(temp_s0, s16 *, 0x5E) = (s16) ((s32) (temp_s1_3 * func_800644B8(temp_s2_2)) >> 0xC);
    }
}
