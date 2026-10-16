#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003E4FC(M2C_UNK, s32, M2C_UNK);       /* extern */
s32 func_8003F270();                                /* extern */
M2C_UNK func_8003F540(M2C_UNK, s32, s32, s32);      /* extern */
s32 func_800445E0();                                /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s16 func_800A9400(s32);                             /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *);       /* extern */
M2C_UNK func_800BB044(void *);                      /* extern */
M2C_UNK func_80157D7C(void *);                      /* extern */
M2C_UNK func_801530EC();                            /* static */
M2C_UNK func_80157814(void *);                      /* static */
extern s32 D_8006CD58;
extern M2C_UNK D_8006DE24;
extern u8 D_80080A84;
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_800DCF50;
extern M2C_UNK D_800DDAB8;
extern M2C_UNK D_80157E40;
extern M2C_UNK D_80157F40;
extern u16 D_80157F6E;

void func_80155560(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_s0;
    s32 temp_v0;
    s32 var_s1;
    s8 var_v0_2;
    s8 var_v1_2;
    u16 temp_v0_2;
    u8 *var_s0;
    u8 temp_v1;
    u8 var_v1;
    void *temp_s0_2;
    void *temp_v1_2;
    void *var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    var_s1 = 0;
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
        switch (temp_v0) {                          /* switch 2 */
        case 7:                                     /* switch 2 */
            var_s1 = 1;
            /* fallthrough */
        case 3:                                     /* switch 2 */
            var_s0 = arg3 + 0xE;
            break;
        case 6:                                     /* switch 2 */
            var_s1 = 1;
            /* fallthrough */
        case 2:                                     /* switch 2 */
            var_s0 = arg3 + 0xB;
            break;
        case 5:                                     /* switch 2 */
            var_s1 = 1;
            /* fallthrough */
        case 1:                                     /* switch 2 */
            var_s0 = arg3 + 8;
            break;
        default:                                    /* switch 2 */
            var_s0 = NULL;
            break;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
        var_v1 = *var_s0;
        if (var_s1 != 0) {
            var_v1 |= 0x80;
        }
        D_80157F6E = (u16) var_v1;
        if (var_s1 != 0) {
            var_v0 = D_800814A8;
            M2C_FIELD(arg3, void **, 0x60) = var_v0;
            goto block_17;
        }
        if (M2C_FIELD(((*var_s0 * 0x14) + &D_8006DE24), u8 *, 0x12) == 2) {
            var_v0 = M2C_FIELD(arg3, void **, 0x60);
            if (var_v0 != NULL) {
block_17:
                temp_v1_2 = M2C_FIELD(var_v0, void **, -0x14);
                M2C_FIELD(arg3, s8 *, 0x72) = (s8) M2C_FIELD(temp_v1_2, u8 *, 0x24);
                M2C_FIELD(arg3, s8 *, 0x73) = (s8) M2C_FIELD(temp_v1_2, u8 *, 0x25);
            }
        } else {
            M2C_FIELD(arg3, void **, 0x60) = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
            var_v0_2 = M2C_FIELD(arg3, s8 *, 0x72);
            var_v1_2 = M2C_FIELD(arg3, s8 *, 0x73);
            if (var_v0_2 < 0) {
                var_v0_2 = -var_v0_2;
            }
            if (var_v1_2 < 0) {
                var_v1_2 = -var_v1_2;
            }
            M2C_FIELD(arg3, s8 *, 0x72) = var_v0_2;
            M2C_FIELD(arg3, s8 *, 0x73) = var_v1_2;
        }
        if (func_800A94A0(arg3, var_s0, var_s1, arg0 + 0x98) != 0) {
            if (var_s1 != 0) {
                D_800DCF50 = *var_s0;
                M2C_FIELD(arg3, u8 *, 0x13) = (u8) (M2C_FIELD(arg3, u8 *, 0x13) | 0x80);
            }
            func_80047784(arg2, *(M2C_FIELD(arg2, M2C_UNK **, 0x2C) + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 2);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            if ((var_s1 != 0) && !(M2C_FIELD(arg3, u8 *, 0x13) & 0x80)) {
                func_80157814(arg3);
                func_80157D7C(arg3);
            } else {
                M2C_FIELD(arg3, u8 *, 0x13) = (u8) (M2C_FIELD(arg3, u8 *, 0x13) & 0x7F);
                D_80157F6E &= 0xFF7F;
                func_800BB044(arg3);
            }
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 1:                                     /* switch 1 */
            if (D_80157F6E & 0x80) {
                if (func_8003F270() == 0) {
                    func_800A56E0(0x300);
                    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (*(func_800A9400(D_80157F6E & 0x7F) + &D_80157F40) - 0x10);
                    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                    return;
                }
            } else {
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 2);
                return;
            }
        } else {
        default:                                    /* switch 1 */
            return;
        }
        break;
    case 2:                                         /* switch 1 */
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - D_80080A84;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if ((s16) temp_v0_2 < 3) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            temp_s0 = func_800A9400(D_80157F6E & 0x7F);
            func_800A56E0(0x1300);
            temp_s0_2 = ((s32) (temp_s0 << 0x11) >> 0xE) + &D_800DDAB8;
            func_8003F540(0, D_8006CD58, M2C_FIELD(temp_s0_2, s32 *, 0), M2C_FIELD(temp_s0_2, s32 *, 4));
            func_8003E4FC(0x15, func_800445E0(), 0);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 3:                                     /* switch 1 */
            if (func_8003F270() != 0) {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
                return;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 4:                                     /* switch 1 */
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x80)) {
                M2C_FIELD(arg2, u8 *, 5) = (u8) (M2C_FIELD(arg2, u8 *, 5) - 1);
            }
            if (((M2C_FIELD(arg2, s8 *, 4) == 4) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
                if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg1, s32 *, 0x10) = 0;
                    M2C_FIELD(arg1, s32 *, 0xC) = 0;
                    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80157E40) {
                        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157E40;
                        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157E40), 0);
                    }
                    if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
                        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
                        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_801530EC;
                        func_800A4ACC(arg3);
                        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFBF);
                        M2C_FIELD(arg3, s8 *, 0x73) = 0;
                        M2C_FIELD(arg3, s8 *, 0x72) = 0;
                        func_800A56E0(0xB4);
                    }
                }
            }
        }
        break;
    }
}
