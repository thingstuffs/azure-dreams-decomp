#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A028(void *);                      /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A2FE0(void *);                      /* extern */
M2C_UNK func_800A32A4(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800ACF88(void *);                      /* extern */
extern M2C_UNK D_80083460;

void func_80167234(void *arg0, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 temp_v1_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (*(s16 *)0x8008346A == 0) {
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x14);
            if ((temp_v1_2 & 0x4000) && !(temp_v1_2 & 0x20000000)) {
                func_800ACF88(arg3);
            }
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            func_800A56E0(0x805);
        case 1:
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
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
