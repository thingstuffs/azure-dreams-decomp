#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003E02C(s16 *, u16 *);                /* extern */
void *func_8003FD64(M2C_UNK, s32);                  /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK, void *); /* extern */
s32 func_800A1618(u8, M2C_UNK);                     /* extern */
s32 func_8015106C(u8, u8, s16, s32, u16 *);         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80150CCC;
extern M2C_UNK D_801526F0;

void func_8015116C(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp18;
    s16 sp20;
    s16 sp22;
    s16 sp24;
    u16 sp28;
    s16 temp_v1_4;
    s16 var_fp;
    s16 var_s6;
    s32 temp_a0_2;
    s32 temp_s1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a3;
    s32 var_s0;
    u16 *temp_s1_2;
    u16 *temp_s2;
    void *temp_a0;
    void *temp_a3;
    void *temp_s0;
    void *temp_s1_3;
    void *temp_v0;
    void *temp_v1;

    var_fp = 0;
    temp_v1 = M2C_FIELD(arg3, void **, 0x60);
    var_s6 = 0;
    if ((temp_v1 == *(s32 *)0x800E3D7C) && (temp_a0 = M2C_FIELD(temp_v1, void **, 0x4C), (temp_a0 != NULL))) {
        if (M2C_FIELD(temp_a0, u8 *, 1) == 0xF) {
            if (M2C_FIELD(temp_a0, u8 *, 0) != 8) {
                goto block_4;
            }
        } else {
            goto block_5;
        }
    } else {
block_4:
block_5:
        if ((*(s16 *)0x8008347C < 0x20) && ((func_800A1618(M2C_FIELD(arg3, u8 *, 0x13), 1) != 0) || (func_800A1618(M2C_FIELD(arg3, u8 *, 0x13), 3) != 0))) {
            temp_s1 = (((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) + 4) & 7;
            if ((func_8015106C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg1, s16 *, 0xA), temp_s1, &sp28) << 0x10) == 0) {
                var_s0 = 0;
                temp_v1_2 = temp_s1 * 2;
                temp_s1_2 = temp_v1_2 + &D_8006CCD8;
                temp_s2 = temp_v1_2 + &D_8006CCE8;
                var_a3 = 0 << 0x10;
loop_10:
                temp_v1_3 = var_s0 * 2;
                if ((func_8015106C((u8) (s16) (M2C_FIELD(arg2, u8 *, 0x24) + *temp_s1_2), (u8) (s16) (M2C_FIELD(arg2, u8 *, 0x25) + *temp_s2), M2C_FIELD(arg1, s16 *, 0xA), var_a3 >> 0x10, &sp28) << 0x10) == 0) {
                    var_s0 += 1;
                    var_a3 = var_s0 << 0x10;
                    if (var_s0 < 8) {
                        goto loop_10;
                    }
                } else {
                    var_fp = *(temp_v1_3 + &D_8006CCD8) + (M2C_FIELD(arg2, u8 *, 0x24) + *temp_s1_2);
                    var_s6 = *(temp_v1_3 + &D_8006CCE8) + (M2C_FIELD(arg2, u8 *, 0x25) + *temp_s2);
                }
                if (var_s0 < 8) {
                    goto block_16;
                }
            } else {
                temp_a0_2 = temp_s1 * 2;
                var_fp = M2C_FIELD(arg2, u8 *, 0x24) + *(temp_a0_2 + &D_8006CCD8);
                var_s6 = M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a0_2 + &D_8006CCE8);
block_16:
                temp_v0 = func_8003FD64(0x100, arg0 - 0x20);
                if (temp_v0 != NULL) {
                    temp_s1_3 = M2C_FIELD(temp_v0, void **, 0xC);
                    temp_s0 = temp_v0 + 0x20;
                    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80150CCC;
                    M2C_FIELD(temp_s0, void **, 0x14) = arg2;
                    M2C_FIELD(temp_s0, void **, 0x18) = arg1;
                    M2C_FIELD(temp_s1_3, s16 *, 0x1E) = 0x1000;
                    M2C_FIELD(temp_s1_3, s16 *, 0x1C) = 0x1000;
                    M2C_FIELD(temp_s1_3, s32 *, 0xC) = 0x808080;
                    M2C_FIELD(temp_s1_3, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28);
                    M2C_FIELD(temp_s1_3, u16 *, 0x12) = (u16) M2C_FIELD(arg2, u16 *, 0x12);
                    temp_v1_4 = *(s16 *)0x80083228;
                    sp20 = (s16) (s8) *((((s32) (temp_v1_4 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 8) & 0xE) + &D_801526F0);
                    sp24 = 0;
                    sp22 = (s16) (s8) M2C_FIELD((&D_801526F0 + (((s32) (temp_v1_4 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 8) & 0xE)), u8 *, 1);
                    func_8003E02C(&sp20, &sp18);
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 2) + sp18);
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(arg1, u16 *, 6) + sp1A);
                    temp_a3 = M2C_FIELD(temp_v0, void **, 8);
                    M2C_FIELD(temp_a3, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + sp1C);
                    func_80047784(temp_s1_3, 0x41, 0, temp_a3);
                    func_8004491C(temp_v0, &D_80045340);
                    M2C_FIELD(temp_v0, void **, 0x20) = (void *) (arg3 + 0x2A);
                    M2C_FIELD(temp_s0, s16 *, 0x20) = 8;
                    M2C_FIELD(temp_s0, s16 *, 0x32) = var_fp;
                    M2C_FIELD(temp_s0, s16 *, 0x34) = var_s6;
                    M2C_FIELD(temp_s0, u16 *, 0x36) = sp28;
                    M2C_FIELD(temp_s0, s16 *, 0x38) = (s16) (M2C_FIELD(arg3, u16 *, 0x14) & 0x2007);
                    M2C_FIELD(temp_s0, u16 *, 0x3A) = (u16) M2C_FIELD(arg2, u16 *, 0x12);
                    M2C_FIELD(temp_s0, void **, 0xC) = (void *) (arg3 - 0x20);
                    M2C_FIELD(temp_s0, void **, 0x10) = arg3;
                    M2C_FIELD(temp_s0, s16 *, 0x3C) = (s16) M2C_FIELD(arg0, u8 *, 0xAC);
                    M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                }
            }
        }
    }
}
