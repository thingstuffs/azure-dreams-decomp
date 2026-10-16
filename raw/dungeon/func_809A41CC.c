#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, s32);                  /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
s32 func_80069EF8();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80175878;
extern M2C_UNK D_80175F9C;

void func_801759CC(s32 arg0, void *arg1, void *arg2) {
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FD64(0x212, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80175878;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, s16 *, 2) = (s16) ((M2C_FIELD(arg1, u16 *, 2) + (func_80069EF8() & 0x3F)) - 0x20);
        M2C_FIELD(temp_s0, s16 *, 6) = (s16) ((M2C_FIELD(arg1, u16 *, 6) + (func_80069EF8() & 0x3F)) - 0x20);
        M2C_FIELD(temp_s0, s16 *, 0xA) = (s16) ((M2C_FIELD(arg1, u16 *, 0xA) + (func_80069EF8() & 0x3F)) - 0x20);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, M2C_UNK **, 8) = &D_80175F9C;
        if (M2C_FIELD(arg2, s32 *, 0x14) & 1) {
            M2C_FIELD(temp_a0, s8 *, 0xC) = 0x20;
        }
        if (M2C_FIELD(arg2, s32 *, 0x14) & 2) {
            M2C_FIELD(temp_a0, s8 *, 0xE) = 0x20;
        }
        if (M2C_FIELD(arg2, s32 *, 0x14) & 4) {
            M2C_FIELD(temp_a0, s8 *, 0xD) = 0x20;
        }
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 6) = 8;
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_v1, s16 *, 0xC) = 0x10;
        M2C_FIELD(temp_v0, void **, 0x20) = arg2;
        M2C_FIELD(temp_v1, void **, 4) = arg1;
    }
}
