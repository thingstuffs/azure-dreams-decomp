#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800A2BDC(void *);                          /* extern */
s32 func_800A6D30();                                /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016EAE4;

void func_8016C0D8(void *arg0, void *arg2, void *arg3) {
    s32 temp_v0;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(*(u16 *)0x80083462 & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
            temp_v0 = M2C_FIELD(arg3, s32 *, 0x14);
            if (temp_v0 >= 0) {
                M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v0 | 0x80000000);
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + ((func_800A6D30() & 7) << 9));
            }
        }
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016EAE4;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016EAE4), 0);
    }
}
