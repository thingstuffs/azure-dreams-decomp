#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80042710(void *, void *);              /* extern */
s32 func_80042900(void *, M2C_UNK);                 /* extern */
M2C_UNK func_80099FDC(void *);                      /* extern */
void *func_800A17E8(u8, M2C_UNK);                   /* extern */
s32 func_800A1BD0(void *);                          /* extern */
M2C_UNK func_800A2B04(M2C_UNK, u8, u8);             /* extern */
M2C_UNK func_800ACB98(void *, s32, s32, void *);    /* extern */
M2C_UNK func_8014FD40(void *, M2C_UNK, void *, void *); /* extern */
extern M2C_UNK D_80083460;

void func_8014F98C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    u8 temp_s1;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1;
    void *temp_v1_2;

    temp_a0 = M2C_FIELD(arg0, void **, 0xA4);
    temp_v1 = M2C_FIELD(temp_a0, void **, 0xC);
    M2C_FIELD(arg2, u8 *, 0x24) = (u8) M2C_FIELD(temp_v1, u8 *, 0x24);
    temp_s2 = temp_a0 + 0x20;
    M2C_FIELD(arg2, u8 *, 0x25) = (u8) M2C_FIELD(temp_v1, u8 *, 0x25);
    M2C_FIELD(arg3, u16 *, 0x88) = (u16) M2C_FIELD(temp_s2, u16 *, 0x88);
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    temp_a0_2 = M2C_FIELD(arg0, void **, 0xA4);
    if (M2C_FIELD(temp_a0_2, u16 *, 0x1E) & 0x8000) {
        if ((M2C_FIELD(temp_s2, u8 *, 0x13) == 0x1E) && (M2C_FIELD(temp_s2, u8 *, 0x28) != 0)) {
            M2C_FIELD(arg3, s8 *, 0x6D) = 1;
        }
        if (M2C_FIELD(arg3, s32 *, 0x14) & 0x4000) {
            temp_v1_2 = *(void **)0x800E3D7C;
            temp_v0 = ((s32) (func_800A1BD0(temp_s2) << 0x10) >> 0xE) + temp_v1_2;
            M2C_FIELD(temp_v0, void **, 0xAC) = arg3;
            M2C_FIELD(temp_v0, s32 *, 0xE4) = 0;
            if (M2C_FIELD(temp_v1_2, void **, 0x60) == temp_s2) {
                M2C_FIELD(temp_v1_2, void **, 0x60) = arg3;
            }
        }
        if (M2C_FIELD(temp_s2, u8 *, 0x13) != 0x1E) {
            if (M2C_FIELD(temp_s2, u8 *, 0x28) == 0) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
            }
        }
        M2C_FIELD(arg3, s32 *, 0x14) = 0;
        M2C_FIELD(arg3, s32 *, 0x1C) = 0;
        func_80042710(arg3, temp_s2);
        M2C_FIELD(arg3, s32 *, 0x14) = (s32) (M2C_FIELD(arg3, s32 *, 0x14) & 0xDFFFFFFF);
        if ((func_80042900(arg3, 1) << 0x10) != 0) {
            var_v0 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x200;
        } else {
            var_v0 = M2C_FIELD(arg3, s32 *, 0x1C) & ~0x200;
        }
        M2C_FIELD(arg3, s32 *, 0x1C) = var_v0;
        M2C_FIELD(arg3, s8 *, 0x13) = 0x1E;
        func_80099FDC(arg0 - 0x20);
        M2C_FIELD(arg3, s32 *, 0x60) = (s32) M2C_FIELD(temp_s2, s32 *, 0x60);
        func_8014FD40(arg0, arg1, arg2, arg3);
        M2C_FIELD(arg0, void **, 0xA4) = NULL;
        return;
    }
    if ((((s8) M2C_FIELD(temp_s2, u8 *, 0x13) - 1) >= 0) && (M2C_FIELD(temp_s2, u8 *, 0x13) != 0x1E) && (M2C_FIELD(arg0, u8 *, 0x9B) == 0)) {
        temp_s1 = M2C_FIELD(temp_a0_2, u8 *, 0x33);
        temp_v0_2 = func_800A17E8(temp_s1, 1);
        if (temp_v0_2 == NULL) {
            var_s0 = 1;
        } else {
            var_s0 = M2C_FIELD(temp_v0_2, u8 *, 1) != temp_s1;
        }
        if (var_s0 != 0) {
            temp_v0_3 = func_800A17E8(temp_s1, 3);
            if (temp_v0_3 != NULL) {
                var_v0_2 = var_s0;
                if (M2C_FIELD(temp_v0_3, u8 *, 1) == temp_s1) {
                    var_s0 = 0;
                    goto block_25;
                }
            } else {
block_25:
                var_v0_2 = var_s0;
            }
            if (var_v0_2 != 0) {
                if (M2C_FIELD(&D_80083460, s32 *, 0xC) == temp_s2) {
                    M2C_FIELD(&D_80083460, s32 *, 0xC) = 0;
                }
                func_800ACB98(temp_s2, M2C_FIELD(temp_s2, s32 *, -0x18), M2C_FIELD(temp_s2, s32 *, -0x14), temp_s2);
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            }
        }
    }
}
