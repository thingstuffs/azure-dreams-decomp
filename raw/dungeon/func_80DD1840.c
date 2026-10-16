#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */
s32 func_800A45D8(u16, u16, s16, s32);              /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */

void func_80159040(void *arg0, void *arg1, void *arg2) {
    s16 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0xA4));
    temp_v0 = M2C_FIELD(arg0, s32 *, 0xA4);
    M2C_FIELD(arg0, s32 *, 0xA4) = (s32) ((temp_v0 * 2) / 3);
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), (temp_v0 * 2) / 3) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0xA4));
        M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0xA8));
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0xA8);
    M2C_FIELD(arg0, s32 *, 0xA8) = (s32) ((temp_v0_2 * 2) / 3);
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), (temp_v0_2 * 2) / 3) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0xA8));
        M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    }
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0xAC));
    M2C_FIELD(arg0, s32 *, 0xAC) = (s32) (M2C_FIELD(arg0, s32 *, 0xAC) + M2C_FIELD(arg0, s32 *, 0xB0));
    temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x10) < temp_s0) {
        M2C_FIELD(arg0, s32 *, 0xAC) = 0;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
        M2C_FIELD(arg1, s32 *, 8) = 0;
        if (M2C_FIELD(arg0, u16 *, 0x98) == 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = 1U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        }
    }
    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (M2C_FIELD(arg0, u16 *, 0x9E) + 1);
    func_800478B8(arg2);
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(void *)0x800814A0 = (s32) (*(void *)0x800814A0 | 0x8000);
    }
}
