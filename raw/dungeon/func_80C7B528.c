#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, void *);               /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, s32);      /* extern */
extern M2C_UNK D_8015E884;
extern M2C_UNK D_8015EA64;

void func_8015ED28(void *arg0, s16 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 var_v1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_v1;
    s32 var_v0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8015EA64;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + arg4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + arg5);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) ((M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + arg6) - 0x64);
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
        func_8004491C(temp_v0, &D_8015E884, temp_lo);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg2;
        M2C_FIELD(temp_s0, s32 *, 8) = arg2;
    }
}
