#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800419EC(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_80099C58(s16, s16, s16, s16, s32);     /* extern */
M2C_UNK func_8009C12C(void *, s32, s16, M2C_UNK);   /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
extern M2C_UNK D_80152884;

void func_801565BC(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    M2C_UNK sp18;
    M2C_UNK sp1C;
    M2C_UNK sp20;
    M2C_UNK sp24;
    M2C_UNK sp28;
    M2C_UNK sp2C;
    M2C_UNK sp30;
    M2C_UNK sp34;
    M2C_UNK var_a0;
    s16 temp_v1;
    s32 temp_fp;
    u16 temp_t0;
    void *temp_a0;
    void *temp_s3;
    void *temp_v1_2;
    void *var_s0;

    sp18 = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 0));
    sp1C = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 4));
    sp20 = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 8));
    sp24 = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 0xC));
    sp28 = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 0x10));
    sp2C = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 0x14));
    sp30 = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 0x18));
    sp34 = M2C_UNALIGNED32(M2C_FIELD(&D_80152884, M2C_UNK *, 0x1C));
    temp_fp = M2C_FIELD(arg0, s32 *, -0x14);
    temp_s3 = M2C_FIELD(arg0, void **, -0x18);
    var_s0 = M2C_FIELD(arg0, s32 *, 0x5C) + 0x20;
    if (var_s0 != arg0) {
        do {
            temp_a0 = M2C_FIELD(var_s0, void **, -0x14);
            if ((M2C_FIELD(temp_a0, u8 *, 0x24) == (arg1 & 0xFFFF)) && (M2C_FIELD(temp_a0, u8 *, 0x25) == (arg2 & 0xFFFF))) {
                temp_v1 = M2C_FIELD(M2C_FIELD(var_s0, void **, -0x18), s16 *, 0xA);
                if (((arg3 + 0x40) >= temp_v1) && ((arg3 - 0x40) < temp_v1)) {
                    if ((u32) (M2C_FIELD(var_s0, u8 *, 0x13) - 0x33) < 4U) {
                        M2C_FIELD(var_s0, s8 *, 0x28) = 0;
                        M2C_FIELD(var_s0, s16 *, 0x64) = -1;
                        func_800419EC(6, 0xC);
                        var_a0 = 0x601;
                        if (M2C_FIELD(var_s0, u8 *, 0x13) == 0x34) {
                            var_a0 = 0x80B;
                        }
                        func_800A56E0(var_a0);
                        temp_t0 = M2C_FIELD(arg0, u16 *, 0x2A);
                        temp_v1_2 = &sp18 + (((s32) (temp_t0 << 0x10) >> 0x17) & 0x1C);
                        func_80099C58((s16) (M2C_FIELD(temp_s3, u16 *, 2) + (M2C_FIELD(temp_v1_2, s16 *, 0) << 5)), (s16) (M2C_FIELD(temp_s3, u16 *, 6) + ((s32) (M2C_FIELD(temp_v1_2, u16 *, 2) << 0x10) >> 0xB)), (s16) (M2C_FIELD(temp_s3, u16 *, 0xA) - 0x20), M2C_FIELD(arg0, s16 *, 0x14), (s32) (s16) temp_t0);
                    } else {
                        func_8009C12C(arg0, temp_fp, (s16) M2C_FIELD(arg0, u16 *, 0x2A), 1);
                    }
                }
            }
            var_s0 = M2C_FIELD(var_s0, s32 *, 0x5C) + 0x20;
        } while (var_s0 != arg0);
    }
}
