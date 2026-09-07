#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s16 D_80083228;
extern u8 D_800DD294[];

void func_80097A68(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x38;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD294;
    func_8003DB94(arg2, M2C_FIELD(D_800DD294, s32 *, ((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C), 0);
    func_800A56E0(0x50A);
    M2C_FIELD(arg0, s16 *, 0x96) = 2;
    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFFEF);
}
