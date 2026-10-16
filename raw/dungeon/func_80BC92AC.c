#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009C93C(void *, M2C_UNK, s16, M2C_UNK, s32); /* extern */
s32 func_800A2B5C(void *);                          /* extern */
M2C_UNK func_800C7930(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_8016CAAC(void *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(*(u16 *)0x80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg0, s8 *, 0x9A) = 0x11;
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
            func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1, 0);
            M2C_FIELD(arg3, s8 *, 0x84) = 0x7C;
            M2C_FIELD(arg3, s8 *, 0x85) = 4;
        }
    }
}
