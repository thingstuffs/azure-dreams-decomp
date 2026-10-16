#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(void *, s32);                     /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
s32 func_800A2BDC(void *);                          /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016A854;
extern M2C_UNK D_8016DFD0;

void func_8016DAD4(void *arg0, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 temp_v0;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x8000)) {
            M2C_FIELD(arg0, u16 *, 0xA6) = (u16) M2C_FIELD(arg2, u16 *, 0x12);
            M2C_FIELD(arg0, s16 *, 0xAA) = (s16) (M2C_FIELD(arg3, u16 *, 0x14) & 7);
        }
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        var_a2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & ~0x2000);
        func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), 0x3000);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016DFD0;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016DFD0), 0);
        temp_v0 = func_800990FC();
        func_80099290(func_80099194(&D_8016A854, func_80099734(arg3, temp_v0)));
        func_800A5720(temp_v0);
    }
}
