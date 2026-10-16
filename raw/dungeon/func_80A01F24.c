#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A028(void *);                      /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A2FE0(void *, u8, s16, s16);        /* extern */
M2C_UNK func_800A32A4(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK, M2C_UNK, s16, s16);  /* extern */
M2C_UNK func_800ACF88(void *);                      /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s32 D_800814A0;
extern M2C_UNK D_80083460;
extern s16 D_8008346A;

void func_80167724(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s16 temp_a2;
    s16 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    u16 temp_v0_2;
    u8 temp_a1;
    u8 temp_v0;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE;
    temp_a2 = *(temp_v1 + &D_8006CCD8);
    temp_a3 = *(temp_v1 + &D_8006CCE8);
    switch (temp_a1) {
    case 0:
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF & 0xFFFBFFFF);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_a2 << 0x10);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a3 << 0x10);
        M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF40000;
        func_800A56E0(0x805, 0xF7FFFFFF, temp_a2, temp_a3);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        /* fallthrough */
    case 1:
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x1C000);
        if (D_8008346A == 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 2:
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x14);
            if ((temp_v1_2 & 0x4000) && !(temp_v1_2 & 0x20000000)) {
                func_800ACF88(arg3);
            }
            M2C_FIELD(arg2, s16 *, 0x10) = 0x60;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 3:
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x1C000);
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                return;
            }
        } else {
        default:
            return;
        }
        break;
    case 4:
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x20000);
        temp_v0 = (u8) M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 0x18;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if ((s16) temp_v0_2 < 0x18) {
            if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
                M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
            }
            func_800A2FE0(arg3, temp_a1, temp_a2, temp_a3);
            func_800A32A4(arg3);
            var_a2 = 0x3000;
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
            func_8009A028(arg3);
            M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
        }
        break;
    }
}
