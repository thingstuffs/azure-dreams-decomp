#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A0;

void func_80164A84(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s16 var_v0;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 temp_v1_4;
    u16 temp_v1_5;
    void *temp_t0;
    void *temp_t1;

    temp_t0 = M2C_FIELD(arg0, void **, 0x40);
    temp_t1 = M2C_FIELD(arg0, void **, 0x44);
    temp_a0 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_v0 = temp_a0 + 0x190;
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v0;
    M2C_FIELD(arg2, u16 *, 6) = (u16) M2C_FIELD(M2C_FIELD(temp_t0, void **, -0x14), u16 *, 6);
    if ((u32) (temp_v0 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (temp_a0 - 0xE70);
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x2C);
    switch (temp_v1) {
    case 0:
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x36) + 1;
        temp_lo = (s32) ((s32) (temp_v1_2 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x38);
        M2C_FIELD(arg0, u16 *, 0x36) = temp_v1_2;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x36) >= 5) {
            var_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1;
block_18:
            M2C_FIELD(arg0, s16 *, 0x2C) = var_v0;
        }
        break;
    case 1:
        if ((u8) M2C_FIELD(temp_t0, u8 *, 0x9B) >= 4U) {
            M2C_FIELD(arg0, u16 *, 0x36) = 0U;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
        }
        if ((M2C_FIELD(temp_t0, u8 *, 0xB3) == 3) && (M2C_FIELD(temp_t0, u8 *, 0xB1) == 2)) {
            M2C_FIELD(arg0, s16 *, 0x2C) = 4;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
        }
        break;
    case 2:
        temp_v1_3 = M2C_FIELD(arg0, u16 *, 0x36) + 1;
        temp_lo_2 = (s32) ((s32) (temp_v1_3 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x38);
        M2C_FIELD(arg0, u16 *, 0x36) = temp_v1_3;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo_2;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo_2;
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo_2;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x36) >= M2C_FIELD(arg0, s16 *, 0x38)) {
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
block_17:
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
            var_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1;
            goto block_18;
        }
        break;
    case 3:
        temp_v1_4 = M2C_FIELD(arg0, u16 *, 0x36) - 1;
        temp_lo_3 = (s32) ((s32) (temp_v1_4 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x38);
        M2C_FIELD(arg0, u16 *, 0x36) = temp_v1_4;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo_3;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo_3;
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo_3;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x36) <= 0) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
        }
        break;
    case 4:
        temp_v1_5 = M2C_FIELD(arg0, u16 *, 0x36) - 1;
        temp_lo_4 = (s32) ((s32) (temp_v1_5 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x38);
        M2C_FIELD(arg0, u16 *, 0x36) = temp_v1_5;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo_4;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo_4;
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo_4;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x36) <= 0) {
            goto block_17;
        }
        break;
    case 5:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x36);
        M2C_FIELD(arg0, u16 *, 0x36) = (u16) (temp_v0_2 - 1);
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg0, s16 *, 0x2C) = 2;
            M2C_FIELD(arg0, u16 *, 0x36) = 0U;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
        }
        break;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_t1, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_t1, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_t1, s32 *, 8);
}
