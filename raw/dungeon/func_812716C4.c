#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(M2C_UNK *, M2C_UNK);              /* extern */
M2C_UNK func_80042B68(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(M2C_UNK *, s32);                  /* extern */
s16 func_8009FD40(M2C_UNK *, void *);               /* extern */
s32 func_800A2C34(M2C_UNK *, M2C_UNK);              /* extern */
s32 func_800A6D30(M2C_UNK *);                       /* extern */
M2C_UNK func_800A9A04(M2C_UNK *);                   /* extern */
M2C_UNK func_800A9A0C(M2C_UNK *);                   /* extern */
M2C_UNK func_800AA258(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK); /* extern */
M2C_UNK func_800AA79C(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AA888(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_80153514();                            /* static */
M2C_UNK func_801556B8(void *, M2C_UNK, void *, M2C_UNK *); /* static */
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80155E94;
extern M2C_UNK D_80155EBC;
extern M2C_UNK D_80155EC4;
extern M2C_UNK D_80155ECC;

void func_80154EC4(void *arg0, M2C_UNK arg1, void *arg2, M2C_UNK *arg3) {
    M2C_UNK *var_a0;
    M2C_UNK *var_a1;
    s32 temp_v1_2;
    s8 temp_v1_4;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_3;
    u8 temp_v1;
    u8 var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80155E94;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80155E94), 0);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            var_v0 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_36:
            M2C_FIELD(arg0, u8 *, 0x9B) = var_v0;
            return;
        }
    default:
        return;
    case 1:
        if (M2C_FIELD(arg0, s16 *, 0x92) == 0) {
            var_a1 = &D_80155EBC;
block_35:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            var_v0 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
            goto block_36;
        }
        break;
    case 2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0 + 1);
        if ((s16) temp_v0 >= 2) {
            var_a1 = &D_80155EC4;
            goto block_35;
        }
        break;
    case 3:
        if ((func_80042900(arg3, 1) << 0x10) != 0) {
            if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x1000) && ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800AA6B4(arg0, arg1, arg2, 0) == 0))) {
                if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
                    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2008)) {
                        func_800AA79C(arg0, arg1, arg2, arg3);
                        return;
                    }
                } else if ((func_800A2C34(arg3) << 0x10) == 0) {
                    temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
                    if (temp_v1_2 & 0x100) {
                        func_800AA258(arg0, arg1, arg2, arg3);
                        return;
                    }
                    if (temp_v1_2 & 0x80000) {
                        func_800AA888(arg0, arg1, arg2, arg3);
                        temp_v1_3 = M2C_FIELD(arg0, u16 *, 0xA2);
                        M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
                        M2C_FIELD(arg0, s16 *, 0x9E) = 0;
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) - temp_v1_3);
                        func_801556B8(arg0, arg1, arg2, arg3);
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
                            goto block_31;
                        }
                    }
                }
            }
        } else {
block_31:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80155ECC;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80155ECC), 0);
            if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                return;
            }
block_39:
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80153514;
        }
        break;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_80155E94;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            goto block_35;
        }
        break;
    case 5:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_2 + 1);
        if ((s16) temp_v0_2 >= 4) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80155E94;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80155E94), 0);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            goto block_39;
        }
        break;
    }
}
