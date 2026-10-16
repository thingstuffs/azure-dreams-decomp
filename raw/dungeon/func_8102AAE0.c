#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(void *, s32);                     /* extern */
s32 func_800A2BDC(void *);                          /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_8014C838;
extern M2C_UNK D_8014C848;
extern M2C_UNK D_80150880;

void func_8014E2E0(void *arg0, void *arg2, void *arg3) {
    s32 temp_v0;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80150880;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80150880), 0);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        temp_v0 = func_800990FC();
        func_80099290(func_80099194(&D_8014C848, func_80099734(M2C_FIELD(arg0, void **, 0xA8), func_80099194(&D_8014C838, func_80099734(arg3, temp_v0)))));
        func_800A5720(temp_v0);
    }
}
