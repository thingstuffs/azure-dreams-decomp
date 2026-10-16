#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80044BB0;
extern M2C_UNK D_80170230;
extern M2C_UNK D_80173B1C;

void func_80170350(void) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80170230;
        func_8004491C(temp_v0, &D_80044BB0);
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v0_2, s16 *, 0xA) = 0;
        M2C_FIELD(temp_v0_2, s16 *, 6) = 0;
        M2C_FIELD(temp_v0_2, s16 *, 2) = 0;
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0;
        M2C_FIELD(temp_v1, s8 *, 0xE) = 0;
        M2C_FIELD(temp_v1, s8 *, 0xD) = 0;
        M2C_FIELD(temp_v1, s8 *, 0xC) = 0;
        M2C_FIELD(temp_v0, M2C_UNK *, 0x48) = M2C_UNALIGNED32(M2C_FIELD(&D_80173B1C, M2C_UNK *, 0));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x4C) = M2C_UNALIGNED32(M2C_FIELD(&D_80173B1C, M2C_UNK *, 4));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x50) = M2C_UNALIGNED32(M2C_FIELD(&D_80173B1C, M2C_UNK *, 8));
        M2C_FIELD(temp_v1, void **, 8) = (void *) (temp_v0 + 0x48);
    }
}
