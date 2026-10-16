#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(void *, M2C_UNK);                 /* extern */
M2C_UNK func_8009A028(void *);                      /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A2FE0(void *, s32, u16);            /* extern */
M2C_UNK func_800A32A4(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800ACF88(void *, s32, u16);            /* extern */
M2C_UNK func_800B8228(s16, s16, s16, void *);       /* extern */
extern M2C_UNK D_80083460;

void func_80155A3C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0;
    s32 temp_lo;
    s32 temp_v1_4;
    u16 temp_a2;
    u8 temp_a0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (*(s16 *)0x8008346A == 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 1U;
            M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
            func_800A56E0(0x805);
            M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
            M2C_FIELD(arg0, s16 *, 0x96) = 0xC;
        case 1:
            temp_v1_2 = (u8) M2C_FIELD(arg2, s32 *, 0xC);
            M2C_FIELD(arg2, s32 *, 0xC) = (s8) (temp_v1_2 - ((s32) temp_v1_2 / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
            temp_v1_3 = M2C_FIELD(arg2, u8 *, 0xD);
            temp_a0 = M2C_FIELD(arg2, u8 *, 0xE);
            M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_v1_3 - ((s32) temp_v1_3 / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
            temp_lo = (s32) temp_a0 / (s16) M2C_FIELD(arg0, s16 *, 0x96);
            M2C_FIELD(arg2, u16 *, 0x1C) = (u16) ((u16) M2C_FIELD(arg2, u16 *, 0x1C) >> 2);
            temp_a2 = M2C_FIELD(arg2, u16 *, 0x1C);
            M2C_FIELD(arg2, u16 *, 0x1E) = (u16) ((u16) M2C_FIELD(arg2, u16 *, 0x1E) >> 1);
            M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (temp_a2 * 3);
            M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) * 3);
            M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_a0 - temp_lo);
            temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
            M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
            if (((temp_v0 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                if (!(M2C_FIELD(arg3, s32 *, 0x14) & 0x20000000) && (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20))) {
                    M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
                }
                temp_v1_4 = M2C_FIELD(arg3, s32 *, 0x14);
                if (!(temp_v1_4 & 0x4000)) {
                    func_800A2FE0(arg3, temp_lo, temp_a2);
                    func_800A32A4(arg3);
                    if ((M2C_FIELD(arg3, u8 *, 0x49) != 0) && !(M2C_FIELD(arg3, u8 *, 0x4B) & 0x20)) {
                        func_800B8228(M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg3, s16 *, 0x88), arg3 + 0x48);
                    }
                    if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
                        var_a2 = 0x3000;
                        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                            var_a2 = 0x300;
                        }
                        func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
                    }
                    func_8009A028(arg3);
                    M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
                    *(s32 *)0x800814A0 |= 0x8000;
                    return;
                }
                if (!(temp_v1_4 & 0x20000000)) {
                    func_800ACF88(arg3, temp_lo, temp_a2);
                }
                func_800A2FE0(arg3);
                func_800A32A4(arg3);
                if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
                    var_a2_2 = 0x3000;
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                        var_a2_2 = 0x300;
                    }
                    func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
                }
                func_8009A028(arg3);
                M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
                *(void *)0x800814A0 = (s32) (*(void *)0x800814A0 | 0x8000);
                func_800A56E0(0x609);
            }
        } else {
            return;
        }
        break;
    }
}
