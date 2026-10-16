#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(void *, M2C_UNK);                 /* extern */
M2C_UNK func_80042B68(void *, M2C_UNK);             /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(void *, s32);                     /* extern */
s16 func_8009FD40(M2C_UNK *, void *);               /* extern */
s32 func_800A2C34(void *, M2C_UNK);                 /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800A9A04(void *);                      /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_800AA258(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK); /* extern */
M2C_UNK func_800AA79C(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AA888(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AD4D0(void *);                      /* extern */
M2C_UNK func_8016AE68();                            /* static */
M2C_UNK func_8016DCEC(void *, M2C_UNK, void *, void *); /* static */
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016E1DC;
extern M2C_UNK D_8016E1E4;

void func_8016D2A4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 temp_v1_3;
    s32 temp_v1_4;
    s8 temp_v1_5;
    u16 temp_v0;
    u16 temp_v1_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E1DC;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E1DC), 0);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
block_55:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 1:
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (!(temp_v1_2 & 0x8000)) {
            if (temp_v1_2 & 0x6000) {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_2 & 0x9FFF);
                temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
                M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
                if (temp_v0 & 1) {
                    func_800A56E0(0x51B);
                }
            }
        }
        if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x1000)) {
            if ((func_80042900(arg3, 1) << 0x10) == 0) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E1E4;
                func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E1E4), 0);
                if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                    if (M2C_FIELD(arg0, u16 *, 0x98) & 0x8000) {
                        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                        goto block_55;
                    }
                    goto block_14;
                }
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                goto block_55;
            }
            if ((M2C_FIELD(arg3, s16 *, 0x64) != 0) && (func_800AA6B4(arg0, arg1, arg2, 0) != 0)) {
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
                if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
                    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2008)) {
                        func_800AA79C(arg0, arg1, arg2, arg3);
                        return;
                    }
                } else {
                    M2C_FIELD(arg0, s16 *, 0xAA) = (s16) ((M2C_FIELD(arg3, u16 *, 0x6A) + 0x800) & 0xFFF);
                    return;
                }
            } else {
                temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x14);
                if (!(temp_v1_3 & 0x8000)) {
                    M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v1_3 | 0x8000);
                    M2C_FIELD(arg3, s16 *, 0x64) = (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x64) + 1);
                    func_800AD4D0(arg3);
                }
                if ((func_800A2C34(arg3) << 0x10) == 0) {
                    temp_v1_4 = M2C_FIELD(arg3, s32 *, 0x1C);
                    if (temp_v1_4 & 0x100) {
                        func_800AA258(arg0, arg1, arg2, arg3);
                        return;
                    }
                    if (temp_v1_4 & 0x80000) {
                        func_800AA888(arg0, arg1, arg2, arg3);
                        func_8016DCEC(arg0, arg1, arg2, arg3);
                        return;
                    }
                    if ((M2C_FIELD(arg3, s8 *, 0x6D) != 0) && (((func_800A2C34(arg3, arg1) << 0x10) == 0) || ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
                        func_800A9A0C(arg3);
                        func_800A9A04(arg3);
                        if ((func_80042900(arg3, 1) << 0x10) != 0) {
                            temp_v1_5 = M2C_FIELD(arg2, s8 *, 0x26);
                            if ((((temp_v1_5 == M2C_FIELD(&D_80082E80, s8 *, 0x26)) && (temp_v1_5 >= 0)) || (func_8009FD40(&D_80082E80, arg2) < 2)) && !(func_800A6D30() & 7)) {
                                func_80042B68(arg3, 1);
                            }
                            if (M2C_FIELD(arg0, u16 *, 0x98) & 0x8000) {
                                func_80042B68(arg3, 1);
                            }
                        }
                        if ((func_80042900(arg3, 1) << 0x10) == 0) {
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E1E4;
                            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E1E4), 0);
                            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                                if (M2C_FIELD(arg0, u16 *, 0x98) & 0x8000) {
                                    M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                                    goto block_55;
                                }
block_14:
                                M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & ~0x200);
                                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8016AE68;
                            } else {
                                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                                goto block_55;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
}
