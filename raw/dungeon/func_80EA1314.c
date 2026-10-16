#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800A2BDC(void *);                          /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80162F08;

void func_80162B14(void *arg0, void *arg2, void *arg3) {
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x18;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162F08;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162F08), 0);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
    }
}
