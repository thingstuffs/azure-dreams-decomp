#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_800248E4;
extern M2C_UNK D_800CEEFC;

void *func_8002495C(void *arg0, void *arg1) {
    void *temp_a0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800248E4;
        func_8004491C(temp_v0, &D_800CEEFC);
        temp_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 2);
        M2C_FIELD(temp_a0, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 6);
        M2C_FIELD(temp_a0, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
        M2C_FIELD(temp_a0, s16 *, 0xE) = (s16) (M2C_FIELD(arg0, u16 *, 2) - M2C_FIELD(arg0, u16 *, 0xE));
        M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (M2C_FIELD(arg0, u16 *, 6) - M2C_FIELD(arg0, u16 *, 0x12));
        M2C_FIELD(temp_a0, s16 *, 0x16) = (s16) (M2C_FIELD(arg0, u16 *, 0xA) - M2C_FIELD(arg0, u16 *, 0x16));
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, u16 *, 0x1C) = (u16) M2C_FIELD(arg1, u16 *, 0x1C);
        M2C_FIELD(temp_v1, u16 *, 0x1E) = (u16) M2C_FIELD(arg1, u16 *, 0x1E);
        M2C_FIELD(temp_v1, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v1, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) M2C_FIELD(arg1, u16 *, 0x14);
    }
    return temp_v0;
}
