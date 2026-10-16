#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(M2C_UNK *, M2C_UNK);              /* extern */
M2C_UNK func_80042B68(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(M2C_UNK *, s32);                  /* extern */
s16 func_8009FD40(M2C_UNK *, void *);               /* extern */
s32 func_800A2C34(M2C_UNK *, void *);               /* extern */
s32 func_800A6D30(M2C_UNK *);                       /* extern */
M2C_UNK func_800A9A04(M2C_UNK *);                   /* extern */
M2C_UNK func_800A9A0C(M2C_UNK *);                   /* extern */
M2C_UNK func_800AA258(void *, void *, void *, M2C_UNK *); /* extern */
s32 func_800AA6B4(void *, void *, void *, M2C_UNK); /* extern */
M2C_UNK func_800AA79C(void *, void *, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AA888(void *, void *, void *, M2C_UNK *); /* extern */
M2C_UNK func_80156218(void *, void *, void *, M2C_UNK *); /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80153400;
extern M2C_UNK D_80157140;
extern M2C_UNK D_80157188;
extern M2C_UNK D_80157190;

void func_80155A2C(void *arg0, void *arg1, void *arg2, M2C_UNK *arg3) {
    M2C_UNK *var_a0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s8 temp_v1_4;
    u16 temp_v0;
    u16 var_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + 0x100000);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157188;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157188), 0);
            var_v0 = M2C_FIELD(&D_80083460, u16 *, 0xA) - 1;
block_35:
            M2C_FIELD(&D_80083460, u16 *, 0xA) = var_v0;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 1:
        if ((func_80042900(arg3, 1) << 0x10) == 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157190;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157190), 0);
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000;
            M2C_FIELD(arg3, s32 *, 0x1C) = temp_v1_2;
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                var_v0_2 = -0x201 & temp_v1_2;
                goto block_41;
            }
            goto block_34;
        }
        if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x1000) && ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800AA6B4(arg0, arg1, arg2, 0) == 0))) {
            if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
                if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2008)) {
                    func_800AA79C(arg0, arg1, arg2, arg3);
                    return;
                }
            } else if ((func_800A2C34(arg3) << 0x10) == 0) {
                temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x1C);
                if (temp_v1_3 & 0x100) {
                    func_800AA258(arg0, arg1, arg2, arg3);
                    return;
                }
                if (temp_v1_3 & 0x80000) {
                    func_800AA888(arg0, arg1, arg2, arg3);
                    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                    func_80156218(arg0, arg1, arg2, arg3);
                    return;
                }
                if ((M2C_FIELD(arg3, s8 *, 0x6D) != 0) && (((func_800A2C34(arg3, arg1) << 0x10) == 0) || ((func_8009A180(arg3, M2C_FIELD(*(void **)0x800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
                    func_800A9A0C(arg3);
                    func_800A9A04(arg3);
                    if ((func_80042900(arg3, 1) << 0x10) != 0) {
                        var_a0 = &D_80082E80;
                        temp_v1_4 = M2C_FIELD(arg2, s8 *, 0x26);
                        if ((((temp_v1_4 == M2C_FIELD(&D_80082E80, s8 *, 0x26)) && (temp_v1_4 >= 0)) || (var_a0 = arg3, ((func_8009FD40(&D_80082E80, arg2) < 2) != 0))) && !(func_800A6D30(var_a0) & 7)) {
                            func_80042B68(arg3, 1);
                        }
                    }
                    if ((func_80042900(arg3, 1) << 0x10) == 0) {
                        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157190;
                        func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157190), 0);
                        var_v1 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000;
                        M2C_FIELD(arg3, s32 *, 0x1C) = var_v1;
                        var_v0_3 = -0x201;
                        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
block_34:
                            M2C_FIELD(arg0, u16 *, 0x96) = 3U;
                            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xBFFF);
                            var_v0 = M2C_FIELD(&D_80083460, u16 *, 0xA) + 1;
                            goto block_35;
                        }
block_40:
                        var_v0_2 = var_v0_3 & var_v1;
block_41:
                        M2C_FIELD(arg3, s32 *, 0x1C) = var_v0_2;
                        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80153400;
                    }
                }
            }
        }
        break;
    case 2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x4000);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFEC0000;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157140;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157140), 0);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            var_v0_3 = M2C_FIELD(arg3, s32 *, 0x1C);
            var_v1 = -0x201;
            goto block_40;
        }
        break;
    }
}
