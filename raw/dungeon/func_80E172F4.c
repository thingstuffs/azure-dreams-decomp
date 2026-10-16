#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A2B04(M2C_UNK, u8, u8);             /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_8016FD04(void *, M2C_UNK, void *);     /* extern */
M2C_UNK func_801702A4(M2C_UNK, void *);             /* extern */
extern M2C_UNK D_8016B094;
extern M2C_UNK D_80170460;

void func_8016EAF4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK var_a0;
    s32 var_v0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_2;
    u16 var_v1;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_2 & 0x8000) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_2 | 0x6000);
            M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
            return;
        }
        var_v0 = temp_v1_2 & 0x6000;
        if (M2C_FIELD(arg2, s8 *, 4) == 1) {
            if (!(temp_v1_2 & 0x1000)) {
                var_v0 = temp_v1_2 & 0x6000;
                goto block_11;
            }
            goto block_13;
        }
block_11:
        if (var_v0 != 0) {
block_13:
            func_8016FD04(arg0, arg1, arg2);
            var_a0 = 1;
            if ((M2C_FIELD(arg3, s32 *, 0x14) & 0x4000) || (var_a0 = 0, ((M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), s32 *, 0x14) & 0x4000) != 0))) {
                func_801702A4(var_a0, arg3);
            }
            func_800A56E0(0x80D);
            var_v1 = 0x20;
block_20:
            M2C_FIELD(arg0, u16 *, 0x96) = var_v1;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        }
    default:
block_24:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80170460;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80170460), 0);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        }
        return;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if (((temp_v0 << 0x10) == 0) || ((M2C_FIELD(arg2, u16 *, 0x14) | 0x8000) != 0)) {
            var_v1 = 4;
            goto block_20;
        }
        goto block_24;
    case 2:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if (((temp_v0_2 << 0x10) == 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            func_800AD594(arg3, 0x400);
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016B094;
            *(s32 *)0x8008346C = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            goto block_24;
        }
        break;
    }
}
