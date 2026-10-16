#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047320(void *, u8, M2C_UNK);         /* extern */
s32 func_80098F70(void *, s32);                     /* extern */
s8 func_8009E924(u8, u8);                           /* extern */
s32 func_8009EB6C(u8, u8, u8, u8);                  /* extern */
s16 func_8009F608(u8, u8, u8, u8, M2C_UNK *);       /* extern */
s32 func_800A0928(void *);                          /* extern */
M2C_UNK func_800A86C4(void *);                      /* extern */
M2C_UNK func_800A8F10(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800A936C(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800A9540(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800A95DC(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800A97C8(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800A9BB8(void *, M2C_UNK, void *, M2C_UNK, void (*)(void *, M2C_UNK, void *, void *)); /* extern */
M2C_UNK func_8016A9C0();                            /* static */
M2C_UNK func_8016ABE0(void *, M2C_UNK, void *, void *); /* static */
s32 func_8016B330(void *, M2C_UNK, void *, M2C_UNK); /* static */
M2C_UNK func_8016C6B8(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_8016CD6C(void *, M2C_UNK, void *);     /* static */
extern u16 D_80013714;
extern void *D_800803DC;
extern M2C_UNK D_80081490;
extern u16 D_800814B4;
extern s16 D_800848E0;
extern u16 D_80085992;
extern M2C_UNK D_800E1D50;
extern M2C_UNK D_8016CE8C;
extern M2C_UNK D_8016CE94;
extern M2C_UNK D_8016CEC4;
extern M2C_UNK D_8016CEE4;

void func_8016A514(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    s32 temp_a1;
    s32 temp_v0_3;
    s8 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1;

    if (D_80085992 & 0x1000) {
        M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
        func_8016A9C0();
        return;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200) {
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_8016CEC4) {
            M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
            M2C_FIELD(arg0, s8 *, 0x9B) = 1;
            M2C_FIELD(arg0, void (**)(void *, M2C_UNK, void *, void *), 0x8C) = NULL;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
            return;
        }
        if (func_800A95DC(arg0, arg1, arg2, &D_8016CE94) == 0) {
            goto block_6;
        }
    } else {
block_6:
        if (!(D_80085992 & 0x2000)) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x100) {
                func_800A8F10(arg0, arg1, arg2, arg3);
                return;
            }
            if (M2C_FIELD(arg0, u8 *, 0x9A) != 0xE) {
                M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
            }
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8016CE8C) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016CE8C;
                func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016CE8C), 0);
                M2C_FIELD(arg2, s8 *, 5) = 1;
                M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
                M2C_FIELD(arg0, s16 *, 0x9E) = 0;
            }
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            if ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800A936C(arg0, arg1, arg2, &D_8016CEE4) == 0)) {
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000) {
                    func_800A9540(arg0, arg1, arg2, arg3);
                    temp_v1 = M2C_FIELD(arg0, u16 *, 0xA2);
                    M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
                    M2C_FIELD(arg0, s16 *, 0x9E) = 0;
                    M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) - temp_v1);
                    func_8016C6B8(arg0, arg1, arg2, arg3);
                    return;
                }
                if ((func_800A0928(arg3) << 0x10) != 0) {
                    func_800A97C8(arg0, arg1, arg2, arg3);
                }
                goto block_19;
            }
        } else {
block_19:
            temp_v0 = func_8009E924(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
            if (M2C_FIELD(arg3, s8 *, 0x6D) > 0) {
                if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x20)) {
                    if ((u16) M2C_FIELD(arg2, u8 *, 0x24) != D_800814B4) {
                        if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                            if (!(D_80085992 & 0x2000) || ((func_80098F70(arg3, M2C_FIELD(D_800803DC, s32 *, 0x58) + 0x20) << 0x10) == 0)) {
                                if (D_80013714 & 8) {
                                    func_8016CD6C(arg0, arg1, arg2);
                                    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
                                    goto block_33;
                                }
                                if ((func_8016B330(arg0, arg1, arg2, 0) << 0x10) != 0) {
                                    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
                                    M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
                                    if (temp_v0_2 & 0x8000) {
                                        goto block_29;
                                    }
                                    goto block_36;
                                }
                            }
                        } else {
block_29:
                            temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
                            switch (temp_v0_3) {
                            case 5:
                            case 6:
                            case 7:
                            case 8:
                            case 9:
                                M2C_FIELD(arg0, void (**)(void *, M2C_UNK, void *, void *), 0x8C) = func_8016A514;
block_33:
                                func_800A86C4(arg3);
                                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                                return;
                            case 1:
                            case 2:
                            case 3:
                                func_800A9BB8(arg0, arg1, arg2, 0, func_8016A514);
                                return;
                            default:
                                goto block_36;
                            }
                        }
                    } else {
block_36:
                        func_8016ABE0(arg0, arg1, arg2, arg3);
                    }
                } else {
                case 12:
                    func_800A86C4(arg3);
                }
            } else {
                temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
                if (!(temp_a1 & 0x2000) && ((temp_v0 < 0) || !(M2C_FIELD(((temp_v0 * 0x14) + &D_800E1D50), u16 *, 0xC) & 2)) && !(temp_a1 & 0x430) && ((func_8009EB6C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80081490, u8 *, 0x24), M2C_FIELD(&D_80081490, u8 *, 0x25)) << 0x10) != 0)) {
                    M2C_FIELD(arg3, s16 *, 0x2A) = func_8009F608(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80081490, u8 *, 0x24), M2C_FIELD(&D_80081490, u8 *, 0x25), &sp18);
                }
            }
        }
    }
}
