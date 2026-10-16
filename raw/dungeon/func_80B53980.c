#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_801689EC;

void func_80169180(void *arg0, void *arg1) {
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    temp_v1 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v1, s16 *, 8) = 0x4A;
        M2C_FIELD(temp_v1, s16 *, 0xC) = 0;
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801689EC;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC;
        M2C_FIELD(temp_a0, u16 *, 0x14) = temp_v0_2;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (temp_v0_2 | 0x80);
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0_2, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_a0_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0xFFE80000);
        temp_a0_3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_3, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0_3, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0_3, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_3, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0_3, s8 *, 0xD) = 0x80;
    }
}
