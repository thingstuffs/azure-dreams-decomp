#include "common.h"
#include "m2c_compat.h"

s32 func_800A2BDC(void *);                          /* extern */
extern M2C_UNK D_80083460;

void func_8015C7D0(void *arg0, void *arg3) {
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    M2C_FIELD(arg0, void (**)(void *, void *), 0x8C) = func_8015C7D0;
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg3, s8 *, 0x6D) = 0;
    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, void (**)(void *, void *), 0x8C) = NULL;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        *(s16 *)0x800DCF5E = 0;
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
    }
}
