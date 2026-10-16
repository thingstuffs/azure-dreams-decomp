#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, void *);               /* extern */
extern M2C_UNK D_8016F5A0;
extern M2C_UNK D_8016FD7C;

void func_8016F86C(void *arg0, s32 arg1, u8 *arg2) {
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_v0 = func_8003FD64(0x12, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016F5A0;
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        temp_v0_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 0xE) = temp_v0_2;
        M2C_FIELD(temp_v1, u16 *, 2) = temp_v0_2;
        temp_v0_3 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 0x12) = temp_v0_3;
        M2C_FIELD(temp_v1, u16 *, 6) = temp_v0_3;
        temp_v0_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        M2C_FIELD(temp_v1, u16 *, 0x16) = temp_v0_4;
        M2C_FIELD(temp_v1, u16 *, 0xA) = temp_v0_4;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, M2C_UNK **, 8) = &D_8016FD7C;
        M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0;
        M2C_FIELD(temp_v1_2, s16 *, 6) = 8;
        temp_v1_3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1_3, s32 *, 0xC) = arg1;
        M2C_FIELD(temp_v1_3, u8 **, 0x10) = arg2;
        M2C_FIELD(temp_v1_3, void **, 0x1C) = (void *) M2C_FIELD(arg0, void **, 8);
        M2C_FIELD(temp_v1_3, u8 *, 0x16) = (u8) *arg2;
        M2C_FIELD(temp_v0, s32 *, 0x20) = 0x40;
        M2C_FIELD(temp_v1_3, s32 *, 4) = 0;
    }
}
