#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK, s32); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_801631C4;

void *func_801632EC(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_v0;
    s32 temp_a2;
    s32 var_a3;
    void *temp_a0;
    void *temp_a1;
    void *temp_v0;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x312);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801631C4;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = M2C_FIELD(arg0, s16 *, 0x2A);
        temp_a1 = temp_v0 + 0x20;
        var_v0 = temp_v1;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        M2C_FIELD(temp_a1, s16 *, 4) = (s16) ((s32) ((temp_v1 - ((var_v0 >> 0xC) << 0xC)) << 0x10) >> 0x19);
        M2C_FIELD(temp_a1, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 0xB0);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28);
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0x100);
        temp_v0_2 = M2C_FIELD(temp_a1, s16 *, 4);
        temp_a2 = temp_v0_2 + 6;
        var_a3 = temp_a2;
        if (temp_a2 < 0) {
            var_a3 = temp_v0_2 + 0xD;
        }
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 6) = -1;
        M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (M2C_FIELD(temp_a1, u16 *, 6) + (temp_a2 - ((var_a3 >> 3) * 8)));
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x10) | 0x20);
        func_80047784(temp_a0, 0x30, 0, var_a3);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_v1_2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_v1_2, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v1_2, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(temp_v1_2, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0) + M2C_FIELD(temp_v1_2, s32 *, 0xC));
        M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 4) + M2C_FIELD(temp_v1_2, s32 *, 0x10));
        return temp_v0;
    }
    return NULL;
}
