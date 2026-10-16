#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
extern M2C_UNK D_801534B8;
extern M2C_UNK D_801580CC;

void func_80154F04(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
block_16:
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if (((s16) temp_v0 == 4) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801580CC;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801580CC), 0);
            func_800A56E0(0x809);
            goto block_16;
        }
        return;
    case 2:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if (((s16) temp_v0_2 == 4) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            goto block_16;
        }
        break;
    case 3:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800AD594(arg3, 0x140);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801534B8;
            *(s32 *)0x8008346C = 0;
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        }
        break;
    }
}
