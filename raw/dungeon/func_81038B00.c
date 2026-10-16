#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(M2C_UNK);                     /* extern */
s32 func_800A45D8(u16, u16, s16);                   /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */

void func_8016E300(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 temp_s0;

    M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) - 1);
    func_800478B8(arg2);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x50));
    M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) + M2C_FIELD(arg0, s32 *, 0x5C));
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x50));
        M2C_FIELD(arg0, s32 *, 0x50) = 0;
        M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x54));
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + M2C_FIELD(arg0, s32 *, 0x60));
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x54));
        M2C_FIELD(arg0, s32 *, 0x54) = 0;
        M2C_FIELD(arg0, s32 *, 0x60) = 0;
    }
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x58));
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + M2C_FIELD(arg0, s32 *, 0x64));
    temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x10) < temp_s0) {
        M2C_FIELD(arg0, s32 *, 0x58) = 0;
        M2C_FIELD(arg0, s32 *, 0x54) = 0;
        M2C_FIELD(arg0, s32 *, 0x50) = 0;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
        M2C_FIELD(arg1, s32 *, 8) = 0;
        M2C_FIELD(arg0, u16 *, 0x1E) = 0U;
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x1E) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
