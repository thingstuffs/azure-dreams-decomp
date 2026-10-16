#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A028(void *);                      /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A2FE0(void *);                      /* extern */
M2C_UNK func_800A32A4(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800ACF88(void *);                      /* extern */
extern M2C_UNK D_80083460;

void func_8015B5B8(void *arg0, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 temp_v1_2;
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (*(s16 *)0x8008346A == 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 1U;
        case 1:
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x14);
            if ((temp_v1_2 & 0x4000) && !(temp_v1_2 & 0x20000000)) {
                func_800ACF88(arg3);
            }
            M2C_FIELD(arg0, u16 *, 0x96) = 6U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg2, s16 *, 0x12) = 0xFF80;
        case 2:
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
            M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
            if ((temp_v0 << 0x10) <= 0) {
                if ((u8) M2C_FIELD(arg2, u8 *, 0xC) >= 0x10U) {
                    M2C_FIELD(arg2, u8 *, 0xC) = (s32) ((s32) M2C_FIELD(arg2, u8 *, 0xC) + 0xFFEFEFF0);
                }
                M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            } else {
                M2C_FIELD(arg2, u8 *, 0xC) = 0x808080;
            }
            if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0) {
                func_800A56E0(0x805);
            }
            if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) || ((u8) M2C_FIELD(arg2, u8 *, 0xC) < 0x10U)) {
                if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
                    M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
                }
                func_800A2FE0(arg3);
                func_800A32A4(arg3);
                var_a2 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
                func_8009A028(arg3);
                M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
                *(s32 *)0x800814A0 |= 0x8000;
            }
        }
        return;
    }
}
