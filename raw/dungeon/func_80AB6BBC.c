#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8015C318;

void func_8015C3BC(void *arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s16 *, 0x3A) = 0x2D;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8015C318;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v0_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v0_2, s8 *, 0xC) = 0;
        M2C_FIELD(temp_v0_2, s8 *, 0xE) = 0;
        M2C_FIELD(temp_v0_2, s8 *, 0xD) = 0;
        M2C_FIELD(temp_v0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v0_2, u16 *, 0x14) | 0x80);
    }
}
