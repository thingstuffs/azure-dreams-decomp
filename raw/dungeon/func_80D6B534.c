#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */
s32 func_800A45D8(u16, u16, s16);                   /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */

void func_8016AD34(void *arg0, void *arg1, void *arg2) {
    s16 temp_s0;
    s16 temp_v0_4;
    s32 temp_lo;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;

    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x34));
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + M2C_FIELD(arg0, s32 *, 0x40));
    temp_s0 = (s16) M2C_FIELD(arg1, u16 *, 0xA);
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 4)) - 0x10) < temp_s0) {
        M2C_FIELD(arg0, s32 *, 0x34) = 0;
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 4)) - 0x11);
        M2C_FIELD(arg1, s32 *, 8) = 0;
        if (M2C_FIELD(arg0, s16 *, 2) == 0) {
            M2C_FIELD(arg0, s16 *, 2) = 1;
        }
    }
    if (M2C_FIELD(arg0, s16 *, 2) == 1) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x2C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x38));
        if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA)) < 0x200) && ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA)) << 0x10) != 0)) {
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x2C));
            M2C_FIELD(arg0, s32 *, 0x2C) = 0;
            M2C_FIELD(arg0, s32 *, 0x38) = 0;
        }
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + M2C_FIELD(arg0, s32 *, 0x3C));
        if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA)) < 0x200) && ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA)) << 0x10) != 0)) {
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x30));
            M2C_FIELD(arg0, s32 *, 0x30) = 0;
            M2C_FIELD(arg0, s32 *, 0x3C) = 0;
        }
    }
    temp_lo = (s32) (M2C_FIELD(arg0, s16 *, 0xC) << 7) / (s16) M2C_FIELD(arg0, s16 *, 0xE);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x18) + 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v0;
    if ((s16) temp_v0 == 3) {
        func_800478B8(arg2);
        M2C_FIELD(arg0, u16 *, 0x18) = 0U;
    }
    temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1C) + 0xC8;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
    if ((u32) (temp_v0_2 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
    }
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) + 0xC8;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
    }
    temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - 1;
    M2C_FIELD(arg0, s16 *, 0xC) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
