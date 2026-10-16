#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_8015CD48(M2C_UNK, void *, void *);     /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_801590F4;
extern M2C_UNK D_8015CF00;

void func_8015CBF8(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800A56E0(0x50C);
        M2C_FIELD(arg0, u16 *, 0x96) = 0xAU;
        func_8015CD48(arg1, arg2, arg3);
        M2C_FIELD(arg3, s8 *, 0x48) = 0;
        M2C_FIELD(arg3, s8 *, 0x49) = 0;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        /* fallthrough */
    case 1:
        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x96);
            M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0 - 1);
            if ((temp_v0 << 0x10) <= 0) {
                goto block_7;
            }
        } else {
block_7:
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CF00;
            func_800AD594(arg3, 0x200);
            func_80047784(arg2, *(M2C_FIELD(arg2, M2C_UNK **, 0x2C) + (((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801590F4;
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, s8 *, 0x6D) = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        }
        return;
    }
}
