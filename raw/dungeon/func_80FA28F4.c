#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(void *, s32);                     /* extern */
s32 func_800A04F0(void *, u8, u8, s16);             /* extern */
s32 func_800A2BDC(void *);                          /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
s32 func_800A6D30();                                /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80158854;
extern M2C_UNK D_8015CB0C;

void func_8015C0F4(void *arg0, void *arg2, void *arg3) {
    s32 temp_v0;
    s32 temp_v0_2;

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
        M2C_FIELD(arg3, s32 *, 0x60) = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A));
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CB0C;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CB0C), 0);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        temp_v0_2 = func_800990FC();
        func_80099290(func_80099194(&D_80158854, func_80099734(arg3, temp_v0_2)));
        func_800A5720(temp_v0_2);
    }
}
