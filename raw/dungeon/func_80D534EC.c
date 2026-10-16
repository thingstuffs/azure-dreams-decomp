#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(void *, M2C_UNK, void *);         /* extern */
extern M2C_UNK D_800E23F8;
extern M2C_UNK D_800E2408;

void func_80158CEC(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s16 var_v0;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_v1_3;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v1_2;
    u16 temp_v1_4;
    void *temp_a3;
    void *temp_t0;
    void *temp_t1;
    void *temp_t3;

    temp_a3 = M2C_FIELD(arg0, void **, 0x40);
    temp_t0 = M2C_FIELD(arg0, void **, 0x44);
    temp_a0 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_t3 = temp_a3 - 0x20;
    temp_t1 = M2C_FIELD(temp_t3, void **, 0xC);
    temp_v0 = temp_a0 + 0x190;
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v0;
    M2C_FIELD(arg2, u16 *, 6) = (u16) M2C_FIELD(temp_t1, u16 *, 6);
    if ((u32) (temp_v0 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (temp_a0 - 0xE70);
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x2C);
    temp_a0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x2C);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x36) + 1;
        temp_lo = (s32) ((s32) (temp_v1_2 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x38);
        M2C_FIELD(arg0, u16 *, 0x36) = temp_v1_2;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x36) >= 5) {
            M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
        }
    default:
block_28:
        if ((func_80042900(temp_a3, 0xA, temp_a3) << 0x10) != 0) {
block_29:
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
        break;
    case 1:
        var_v0 = temp_a0_2 + 1;
        if ((M2C_FIELD(temp_a3, u8 *, 0x9A) == 0x19) || (var_v0 = temp_a0_2 + 1, (M2C_FIELD(temp_a3, u8 *, 0xB5) == 0))) {
            M2C_FIELD(arg0, s16 *, 0x2C) = var_v0;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
        }
        if (M2C_FIELD(temp_a3, u8 *, 0x9A) == 1) {
            M2C_FIELD(arg0, s16 *, 0x2C) = 3;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
        }
        if ((M2C_FIELD(temp_a3, s32 *, 0x14) & 0x100000) && (M2C_FIELD(*(void **)0x800E3D7C, u8 *, 0x9A) != 0x28)) {
            M2C_FIELD(arg0, s16 *, 0x2C) = 3;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
        }
        if (M2C_FIELD(temp_t3, u16 *, 0x1E) & 0x8000) {
            M2C_FIELD(arg0, s16 *, 0x2C) = 3;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
        }
        temp_v1_3 = M2C_FIELD(temp_t1, s32 *, 0x2C);
        if ((temp_v1_3 == &D_800E23F8) || (temp_v1_3 == &D_800E2408)) {
            M2C_FIELD(arg0, s16 *, 0x2C) = 3;
            M2C_FIELD(arg0, s16 *, 0x38) = 0x14;
            M2C_FIELD(arg0, u16 *, 0x36) = 0x14U;
        }
        M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_t0, s32 *, 0);
        M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_t0, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_t0, s32 *, 8);
block_27:
        goto block_28;
    case 3:
        M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_t0, s32 *, 0);
        M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_t0, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_t0, s32 *, 8);
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) M2C_FIELD(temp_t1, u16 *, 0x1C);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) M2C_FIELD(temp_t1, u16 *, 0x1E);
        /* fallthrough */
    case 2:
        temp_v1_4 = M2C_FIELD(arg0, u16 *, 0x36) - 1;
        temp_lo_2 = (s32) ((s32) (temp_v1_4 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x38);
        M2C_FIELD(arg0, u16 *, 0x36) = temp_v1_4;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo_2;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo_2;
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo_2;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x36) > 0) {
            goto block_27;
        }
        goto block_29;
    }
}
