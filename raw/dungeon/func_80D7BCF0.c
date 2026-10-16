#include "common.h"
#include "m2c_compat.h"

s32 func_800A2B5C(void *);                          /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */

void func_801634F0(void *arg0, void *arg3) {
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(*(u16 *)0x80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        func_800A4ACC(arg3);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    }
}
