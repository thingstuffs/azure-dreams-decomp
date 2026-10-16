#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(void *, M2C_UNK *, M2C_UNK);  /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, s32);      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC70;
extern M2C_UNK D_80158A84;

void func_80158DDC(void *arg0, s16 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 var_v1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_v1;
    s32 var_v0;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80158A84;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + arg4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + arg5);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) ((M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + arg6) - 0x14);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x36) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 0x38) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        var_v1 = arg3;
        M2C_FIELD(temp_s0, u16 *, 0x3A) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        if (arg3 < 0) {
            var_v1 = arg3 + 7;
        }
        temp_v1 = var_v1 >> 3;
        temp_lo = (s32) -(arg4 << 0x10) / temp_v1;
        M2C_FIELD(temp_s0, s32 *, 0x40) = (s32) (temp_lo / 2);
        temp_lo_2 = (s32) -(arg5 << 0x10) / temp_v1;
        M2C_FIELD(temp_s0, s32 *, 0x44) = (s32) (temp_lo_2 / 2);
        temp_lo_3 = (s32) -(arg6 << 0x10) / temp_v1;
        M2C_FIELD(temp_s0, s32 *, 0x48) = (s32) (temp_lo_3 / 2);
        M2C_FIELD(temp_s0, s32 *, 0x4C) = (s32) (temp_lo / 4);
        M2C_FIELD(temp_s0, s32 *, 0x50) = (s32) (temp_lo_2 / 4);
        var_v0 = temp_lo_3;
        if (var_v0 < 0) {
            var_v0 += 3;
        }
        M2C_FIELD(temp_s0, s32 *, 0x54) = (s32) (var_v0 >> 2);
        M2C_FIELD(temp_s0, s16 *, 0x14) = arg1;
        M2C_FIELD(temp_s0, s16 *, 0x32) = arg3;
        M2C_FIELD(temp_s0, s16 *, 0x34) = arg3;
        func_8004491C(temp_v0, &D_80045340, temp_lo);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s8 *, 0xE) = 0;
        M2C_FIELD(temp_a0, s8 *, 0xD) = 0;
        M2C_FIELD(temp_a0, s8 *, 0xC) = 0;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg2;
        M2C_FIELD(temp_s0, s32 *, 8) = arg2;
        func_8003DB94(temp_a0, &D_800DEC70, 0);
    }
}
