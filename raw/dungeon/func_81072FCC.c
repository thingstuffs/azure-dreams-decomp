#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(M2C_UNK, u8, u8);             /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK, u16);                /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
extern M2C_UNK D_80158F68;
extern M2C_UNK D_8015BFE8;
extern M2C_UNK D_8015C010;

void func_8015A7CC(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK var_a1;
    u16 temp_a1;
    u16 var_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_a1 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_a1;
    switch (temp_v1) {                              /* irregular */
    case 0x0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            return;
        }
        if (M2C_FIELD(arg0, u16 *, 0x98) & 0x8000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015C010;
            var_v0 = 0xA;
        } else {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015BFE8;
            var_v0 = 4;
        }
        M2C_FIELD(arg0, u16 *, 0x96) = var_v0;
        func_80047784(arg2, *(M2C_FIELD(arg2, M2C_UNK **, 0x2C) + (((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 0x1:
        if ((temp_a1 << 0x10) <= 0) {
            func_800A56E0(0x809, temp_a1);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            return;
        }
        return;
    case 0xFF:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            var_a1 = 0x100;
            if (M2C_FIELD(arg0, u16 *, 0x98) & 0x8000) {
                var_a1 = 0x800;
            }
            func_800AD594(arg3, var_a1);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80158F68;
            *(s32 *)0x8008346C = 0;
            func_800A4ACC(arg3);
            if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                return;
            }
            *(void **)0x800E3DE8 = arg3 - 0x20;
        }
        break;
    }
}
