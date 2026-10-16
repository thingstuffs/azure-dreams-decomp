#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(void *, s32);                     /* extern */
s32 func_800A2C34(void *, M2C_UNK);                 /* extern */
M2C_UNK func_800A9A04(void *);                      /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_800AA258(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK); /* extern */
M2C_UNK func_800AA888(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_80173D10(void *, M2C_UNK, void *, void *); /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_801711A4;
extern M2C_UNK D_801741C4;
extern M2C_UNK D_801741CC;

void func_801739D0(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 temp_v1_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801741CC;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801741CC), 0);
block_23:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801741C4;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801741C4), 0);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
            goto block_23;
        }
        if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x1000) && ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800AA6B4(arg0, arg1, arg2, 0) == 0)) && ((func_800A2C34(arg3) << 0x10) == 0)) {
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
            if (temp_v1_2 & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                return;
            }
            if (temp_v1_2 & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                func_80173D10(arg0, arg1, arg2, arg3);
                return;
            }
            if ((M2C_FIELD(arg3, s8 *, 0x6D) != 0) && (((func_800A2C34(arg3, arg1) << 0x10) == 0) || ((func_8009A180(arg3, M2C_FIELD(*(void **)0x800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
                func_800A9A0C(arg3);
                func_800A9A04(arg3);
                if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
                    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801741C4;
                    func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801741C4), 0);
                    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
                    M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                    goto block_23;
                }
            }
        }
        break;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & ~0x208);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801711A4;
        }
        break;
    }
}
