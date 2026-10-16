#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, void *);               /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_801505F0;

void func_80150690(void *arg0) {
    void *temp_a0;
    void *temp_a1;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x112, arg0);
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801505F0;
        temp_a1 = temp_v0 + 0x20;
        M2C_FIELD(temp_a1, void **, 0x18) = (void *) M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_a1, s32 *, 0x1C) = (s32) M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_a0, u16 *, 0x12) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x12) - 0x80);
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x18), s32 *, 0x28);
        func_80047784(temp_a0, 0x44, 0);
        func_8004491C(temp_v0, &D_80045340);
    }
}
