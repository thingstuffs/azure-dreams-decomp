#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */
s32 func_800A45D8(u16, u16, s16, s32);              /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */

void func_8015342C(void *arg0, void *arg1, void *arg2) {
    s16 temp_s0;
    s16 temp_s0_2;
    s16 temp_s4;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;

    if (M2C_FIELD(arg0, s16 *, 0) == 0) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x60));
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x60);
        M2C_FIELD(arg0, s32 *, 0x60) = (s32) ((temp_v0 * 2) / 3);
        if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), (temp_v0 * 2) / 3) << 0x10) != 0) {
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x60));
            M2C_FIELD(arg0, s32 *, 0x60) = 0;
            M2C_FIELD(arg0, s32 *, 0x6C) = 0;
        }
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x64));
        temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x64);
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) ((temp_v0_2 * 2) / 3);
        if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), (temp_v0_2 * 2) / 3) << 0x10) != 0) {
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x64));
            M2C_FIELD(arg0, s32 *, 0x64) = 0;
            M2C_FIELD(arg0, s32 *, 0x70) = 0;
        }
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x68));
        M2C_FIELD(arg0, s32 *, 0x68) = (s32) (M2C_FIELD(arg0, s32 *, 0x68) + M2C_FIELD(arg0, s32 *, 0x74));
        temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
        if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x10) < temp_s0) {
            M2C_FIELD(arg0, s32 *, 0x68) = 0;
            M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
            M2C_FIELD(arg1, s32 *, 8) = 0;
            if (M2C_FIELD(arg0, s16 *, 0x1A) == 0) {
                M2C_FIELD(arg0, s16 *, 0x1A) = 1;
                M2C_FIELD(arg0, u16 *, 0x24) = 0U;
            }
        }
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x26) + 1;
        M2C_FIELD(arg0, u16 *, 0x26) = temp_v0_3;
        if (!(temp_v0_3 & 3)) {
            func_800478B8(arg2);
        }
        temp_v0_4 = M2C_FIELD(arg2, u16 *, 0x1C) + 0x64;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_4;
        if ((u32) (temp_v0_4 & 0xFFFF) >= 0x2001U) {
            M2C_FIELD(arg2, u16 *, 0x1C) = 0x2000U;
        }
        temp_v0_5 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x64;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_5;
        if ((u32) (temp_v0_5 & 0xFFFF) >= 0x2001U) {
            M2C_FIELD(arg2, u16 *, 0x1E) = 0x2000U;
        }
        temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x24) - 1;
        M2C_FIELD(arg0, u16 *, 0x24) = temp_v0_6;
        if ((temp_v0_6 << 0x10) <= 0) {
            M2C_FIELD(arg0, s16 *, 0x1A) = 0;
            M2C_FIELD(arg0, s16 *, 0) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0) + 1);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
    }
    temp_s4 = M2C_FIELD(arg0, s16 *, 0);
    if (temp_s4 == 1) {
        if (M2C_FIELD(arg0, s16 *, 0x1A) == 0) {
            M2C_FIELD(arg0, s16 *, 0x1A) = temp_s4;
            M2C_FIELD(arg0, u16 *, 0x24) = 0x14U;
            M2C_FIELD(arg0, u16 *, 0x26) = 0x14U;
            M2C_FIELD(arg0, s32 *, 0x64) = 0;
            M2C_FIELD(arg0, s32 *, 0x60) = 0;
        }
        temp_v0_7 = M2C_FIELD(arg2, u16 *, 0x1C) + 0xC8;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_7;
        if ((u32) (temp_v0_7 & 0xFFFF) >= 0x2001U) {
            M2C_FIELD(arg2, u16 *, 0x1C) = 0x2000U;
        }
        temp_v0_8 = M2C_FIELD(arg2, u16 *, 0x1E) + 0xC8;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_8;
        if ((u32) (temp_v0_8 & 0xFFFF) >= 0x2001U) {
            M2C_FIELD(arg2, u16 *, 0x1E) = 0x2000U;
        }
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x68));
        M2C_FIELD(arg0, s32 *, 0x68) = (s32) (M2C_FIELD(arg0, s32 *, 0x68) + M2C_FIELD(arg0, s32 *, 0x74));
        temp_s0_2 = M2C_FIELD(arg1, s16 *, 0xA);
        if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x10) < temp_s0_2) {
            M2C_FIELD(arg0, s32 *, 0x68) = 0;
            M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
            M2C_FIELD(arg1, s32 *, 8) = 0;
            if (M2C_FIELD(arg0, s16 *, 0x1A) == 0) {
                M2C_FIELD(arg0, s16 *, 0x1A) = temp_s4;
                M2C_FIELD(arg0, u16 *, 0x24) = 0U;
            }
        }
        temp_lo = (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x24) << 7) / (s16) M2C_FIELD(arg0, u16 *, 0x26);
        M2C_FIELD(arg2, s8 *, 0xE) = 0;
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
        temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x24) - 1;
        M2C_FIELD(arg0, u16 *, 0x24) = temp_v0_9;
        if ((temp_v0_9 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(void *)0x800814A0 = (s32) (*(void *)0x800814A0 | 0x8000);
        }
    }
}
