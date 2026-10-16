#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80044BB0;
extern M2C_UNK D_800A5AF0;

void func_8001F354(s16 arg0, s16 arg1, s32 arg2, s32 arg3) {
    s32 var_v0;
    void *temp_a0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800A5AF0;
        func_8004491C(temp_v0, &D_80044BB0);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, s16 *, 2) = (s16) (arg0 + 0x280);
        M2C_FIELD(temp_v1, s16 *, 6) = arg1;
        M2C_FIELD(temp_v1, s16 *, 0xA) = 1;
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x2000;
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s32 *, 8) = arg3;
        if ((arg2 << 0x10) != 0) {
            var_v0 = 0x202080;
        } else {
            var_v0 = 0x808080;
        }
        M2C_FIELD(temp_a0, s32 *, 0xC) = var_v0;
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        temp_v1_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_v1_2, s16 *, 6) = 0x18;
        M2C_FIELD(temp_v1_2, s16 *, 8) = arg0;
    }
}
