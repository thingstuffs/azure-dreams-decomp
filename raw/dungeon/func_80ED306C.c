#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800478E8(void *, M2C_UNK *, M2C_UNK);  /* extern */
M2C_UNK func_800A48F0(void *, M2C_UNK, s32);        /* extern */
s32 func_800A6D30(void *);                          /* extern */
M2C_UNK func_800A9C18(void *, void *, void *, s16); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D71A8;
extern M2C_UNK D_800D78C0;
extern M2C_UNK D_80152B64;
extern M2C_UNK D_801531A4;
extern M2C_UNK D_8015618C;
extern M2C_UNK D_801561CC;

void *func_8015286C(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    void *sp10;
    s32 sp14;
    s32 temp_a3;
    s32 temp_t1_2;
    s32 temp_v1;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    s32 var_v1;
    void *temp_a0;
    void *temp_s0;
    void *temp_s4;
    void *temp_t1;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s3;
    void *var_s5;

    var_s3 = NULL;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80152B64;
        M2C_FIELD(var_s3, s8 *, 0x13) = 0x21;
        func_8004491C(temp_v0, &D_80045340);
        temp_t1 = M2C_FIELD(temp_v0, void **, 8);
        sp10 = temp_t1;
        M2C_FIELD(temp_t1, s16 *, 0xA) = arg3;
        temp_s4 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v1 = arg0 & 3;
        M2C_FIELD(temp_s4, M2C_UNK **, 0x2C) = &D_8015618C;
        M2C_FIELD(temp_s4, s8 *, 0x24) = arg1;
        M2C_FIELD(temp_s4, s8 *, 0x25) = arg2;
        if (temp_v1 == 1) {
            var_v0 = M2C_FIELD(var_s3, s32 *, 0x14) | 0x6000;
            var_v1 = M2C_FIELD(var_s3, s32 *, 0x1C) | 0x6000;
            goto block_5;
        }
        if (temp_v1 >= 2) {
            var_v0 = M2C_FIELD(var_s3, s32 *, 0x14) | 0x2000;
            var_v1 = M2C_FIELD(var_s3, s32 *, 0x1C) | 0x2000;
block_5:
            M2C_FIELD(var_s3, s32 *, 0x14) = var_v0;
            M2C_FIELD(var_s3, s32 *, 0x1C) = var_v1;
        } else if (((arg0 & ~3) << 0x10) == 0) {
            if (!(M2C_FIELD(var_s3, s32 *, 0x14) & 0x200)) {
                if (func_800A6D30(temp_v0) & 1) {
                    M2C_FIELD(var_s3, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s3, s32 *, 0x1C) | 0x200);
                    func_800A48F0(var_s3, 1, (func_800A6D30(temp_v0) & 0x3F) | 0x20);
                    M2C_FIELD(temp_s4, M2C_UNK **, 0x2C) = &D_801561CC;
                }
            }
        }
        func_800A9C18(temp_v0, sp10, temp_s4, arg0);
        var_s5 = var_s3;
        sp14 = 0;
        M2C_FIELD(var_s3, s8 *, 0x9A) = 0xFF;
        M2C_FIELD(var_s3, s8 *, 0x9C) = -1;
        M2C_FIELD(var_s3, M2C_UNK **, 0x8C) = &D_801531A4;
        M2C_FIELD(var_s3, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s3, s32 *, 0x1C) | 0x40000);
        M2C_FIELD(var_s3, s16 *, 0x92) = -0x10;
        M2C_FIELD(var_s3, s16 *, 0xA8) = 0;
        M2C_FIELD(var_s3, s16 *, 0x9E) = 1;
        M2C_FIELD(var_s3, u16 *, 0x98) = (u16) (M2C_FIELD(var_s3, u16 *, 0x98) | 0x4000);
        do {
            temp_v0_2 = func_8003FD64(0x112, &D_80083498);
            M2C_FIELD(var_s5, void **, 0xA4) = temp_v0_2;
            if (temp_v0_2 != NULL) {
                temp_s0 = temp_v0_2 + 0x20;
                M2C_FIELD(temp_s0, s16 *, 2) = 1;
                var_s2 = 0;
                var_s1 = 8;
                do {
                    temp_a0 = temp_s0 + var_s1;
                    M2C_FIELD(temp_s0, u16 *, 4) = (u16) (M2C_FIELD(temp_s0, u16 *, 4) | 0x8000);
                    temp_a3 = M2C_FIELD(temp_s4, s32 *, 0x28);
                    M2C_FIELD(temp_a0, s16 *, 0x10) = 0x60;
                    M2C_FIELD(temp_a0, s32 *, 0x28) = temp_a3;
                    M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
                    var_s1 += 0x30;
                    M2C_FIELD(temp_a0, s32 *, 0xC) = 0xC0C0C0;
                    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (M2C_FIELD(temp_s4, u16 *, 0x12) - 0x80);
                    var_s2 += 1;
                    M2C_FIELD(M2C_FIELD(var_s5, void **, 0xA4), M2C_UNK **, 0x10) = &D_800D78C0;
                    func_80047784(temp_a0, 0x27, 0, temp_a3);
                    M2C_FIELD(temp_s0, s16 *, 6) = 0;
                    func_800478E8(temp_s4, &D_800D71A8, 0);
                    M2C_FIELD(temp_s0, void **, 0x98) = (void *) (temp_v0 + 0x1E);
                } while (var_s2 < M2C_FIELD(temp_s0, s16 *, 2));
            }
            var_s5 += 4;
            temp_t1_2 = sp14 + 1;
            sp14 = temp_t1_2;
        } while (temp_t1_2 < M2C_FIELD(var_s3, s16 *, 0x9E));
        func_800AA36C(var_s3, sp10, temp_s4, var_s3);
    }
    return var_s3;
}
