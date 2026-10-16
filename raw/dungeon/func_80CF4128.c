#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80164EF4;
extern M2C_UNK D_80169EDC;

void func_80165928(void *arg1) {
    void *temp_a0;
    void *temp_a3;
    void *temp_a3_2;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x18) = 0x1C;
        M2C_FIELD(temp_v1, s16 *, 0x1A) = 0x1C;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80164EF4;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_a3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a3, u16 *, 0x14) | 0xC);
        temp_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_a0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0xFFB00000);
        temp_a3_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3_2, s16 *, 0x1E) = 0x190;
        M2C_FIELD(temp_a3_2, s16 *, 0x1C) = 0x190;
        M2C_FIELD(temp_a3_2, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a3_2, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a3_2, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_v0, M2C_UNK *, 0x44) = M2C_UNALIGNED32(M2C_FIELD(&D_80169EDC, M2C_UNK *, 0));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x48) = M2C_UNALIGNED32(M2C_FIELD(&D_80169EDC, M2C_UNK *, 4));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x4C) = M2C_UNALIGNED32(M2C_FIELD(&D_80169EDC, M2C_UNK *, 8));
        M2C_FIELD(temp_a3_2, void **, 8) = (void *) (temp_v0 + 0x44);
    }
}
