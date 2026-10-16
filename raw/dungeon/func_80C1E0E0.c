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
M2C_UNK func_8016E250(void *, void *, void *, M2C_UNK *); /* static */
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016E49C;
extern M2C_UNK D_8016E4EC;
extern M2C_UNK D_8016E4F4;
extern M2C_UNK D_8016E4FC;
static M2C_UNK RO_8016B3A8;                         /* unable to generate initializer: unknown type; const */

void func_8016D8E0(void *arg0, void *arg1, void *arg2, M2C_UNK *arg3) {
    M2C_UNK *var_a0;
    M2C_UNK *var_a1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v1;
    s8 temp_v1_4;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E4FC;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E4FC), 0);
block_10:
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
            return;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF & 0xFFFBFFFF);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            var_a1 = &D_8016E4F4;
            M2C_FIELD(arg1, s32 *, 0x14) = -0x80000;
block_40:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
block_41:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
    default:
        return;
    case 1:
        temp_v1_2 = M2C_FIELD(arg1, s32 *, 0x14);
        if (temp_v1_2 <= 0xFFFFF) {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (temp_v1_2 + 0x20000);
        }
        if (M2C_FIELD(arg0, s32 *, 0x90) >= 0) {
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E4FC;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E4FC), 0);
            func_800A9A0C(arg3);
            goto block_10;
        }
        break;
    case 2:
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
        if ((func_80042900(arg3, 1) << 0x10) == 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E4F4;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E4F4), 0);
            var_v1 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000;
            M2C_FIELD(arg3, s32 *, 0x1C) = var_v1;
            var_v0 = -0x201;
            if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                goto block_41;
            }
            goto block_46;
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
                    func_8016E250(arg0, arg1, arg2, arg3);
                    return;
                }
                if ((M2C_FIELD(arg3, s8 *, 0x6D) != 0) && (((func_800A2C34(arg3, arg1) << 0x10) == 0) || ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
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
                        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E4F4;
                        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E4F4), 0);
                        var_v1 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000;
                        M2C_FIELD(arg3, s32 *, 0x1C) = var_v1;
                        var_v0 = -0x201;
                        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                            goto block_41;
                        }
block_46:
                        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (var_v0 & var_v1);
                        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &RO_8016B3A8;
                    }
                }
            }
        }
        break;
    case 3:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_8016E4EC;
            goto block_40;
        }
        break;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = -0x80000;
            M2C_FIELD(arg0, s16 *, 0xA8) = 8;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xBFFF);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E49C;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E49C), 0);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
            M2C_FIELD(arg0, u8 *, 0x9B) = 0x10U;
            return;
        }
        break;
    case 16:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x4000);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            var_v0 = M2C_FIELD(arg3, s32 *, 0x1C);
            var_v1 = -0x201;
            goto block_46;
        }
        break;
    }
}
