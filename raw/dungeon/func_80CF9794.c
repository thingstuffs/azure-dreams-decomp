#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */
s32 func_800A45D8(u16, u16, s16);                   /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */

void func_8015EF94(void *arg0, void *arg1, void *arg2) {
    s16 temp_s0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + M2C_FIELD(arg0, s32 *, 0x4C));
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) + M2C_FIELD(arg0, s32 *, 0x50));
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x44));
        M2C_FIELD(arg0, s32 *, 0x44) = 0;
        M2C_FIELD(arg0, s32 *, 0x50) = 0;
    }
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + M2C_FIELD(arg0, s32 *, 0x54));
    temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x10) < temp_s0) {
        M2C_FIELD(arg0, s32 *, 0x48) = 0;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
        M2C_FIELD(arg1, s32 *, 8) = 0;
        if (M2C_FIELD(arg0, s16 *, 0xE) == 0) {
            M2C_FIELD(arg0, s16 *, 0xE) = 1;
            M2C_FIELD(arg0, u16 *, 0x18) = 0U;
        }
    }
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x1A) + 1;
    M2C_FIELD(arg0, u16 *, 0x1A) = temp_v0;
    if (!(temp_v0 & 3)) {
        func_800478B8(arg2);
    }
    temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1C) + 0x64;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
    if ((u32) (temp_v0_2 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
    }
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x64;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
    }
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(void *)0x800814A0 = (s32) (*(void *)0x800814A0 | 0x8000);
    }
}
