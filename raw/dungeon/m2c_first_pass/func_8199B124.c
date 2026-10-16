#include "common.h"
#include "m2c_compat.h"

void *func_80024924(s32 arg0, s16 arg1, s16 arg2, s16 arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    void *temp_a1;
    void *temp_a2;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = (void *(*)(M2C_UNK, s32))0x8003FD64(0x212, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0x80024784;
        (M2C_UNK (*)(void *, M2C_UNK))0x8004491C(temp_v0, 0x800CEEFC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16) M2C_FIELD(arg4, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16) M2C_FIELD(arg4, u16 *, 6);
        temp_a2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0xE) = arg1;
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16) M2C_FIELD(arg4, u16 *, 0xA);
        M2C_FIELD(temp_a2, s16 *, 0x18) = arg1;
        M2C_FIELD(temp_v1, s16 *, 0x12) = arg2;
        M2C_FIELD(temp_a2, s16 *, 0x1A) = arg2;
        M2C_FIELD(temp_v1, s16 *, 0x16) = arg3;
        M2C_FIELD(temp_a2, s16 *, 0x1C) = arg3;
        temp_a1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a1, s32 *, 8) = arg5;
        M2C_FIELD(temp_a1, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a1, s32 *, 0xC) = 0x808080;
        if ((s16) arg6 != 0) {
            M2C_FIELD(temp_a1, s16 *, 0x10) = (s16) (((s16) arg6 - 1) << 5);
            M2C_FIELD(temp_a1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a1, u16 *, 0x14) | 0xC);
        }
        M2C_FIELD(temp_a2, s16 *, 0x2E) = 8;
        M2C_FIELD(temp_a2, s16 *, 0x3C) = 0x80;
        M2C_FIELD(temp_a2, s32 *, 0x14) = arg7;
        M2C_FIELD(temp_a2, s16 *, 0x32) = (s16) arg8;
    }
    return temp_v0;
}
