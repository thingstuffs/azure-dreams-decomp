#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();        /* extern */
s32 func_800A6D30();                                /* extern */
extern s16 D_80083228;
extern u8 D_800DD294[];

void func_80097898(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x39;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    if (!(func_800A6D30() & 3)) {
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & ~0x620);
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD294;
    func_8003DB94(arg2, M2C_FIELD(D_800DD294, s32 *, ((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C), 0);
}
