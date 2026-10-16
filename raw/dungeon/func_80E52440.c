#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800A2BDC(void *);                          /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_8015E670;

void func_8015BC40(void *arg0, void *arg2, void *arg3) {
    if (M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) {
        M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
        return;
    }
    if ((func_800A2BDC(arg3) << 0x10) == 0) {
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015E670;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015E670), 0);
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    }
}
