#include "common.h"
#include "m2c_compat.h"

s32 func_8003F270();                                /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *);       /* extern */
M2C_UNK func_800BB044(void *);                      /* extern */
M2C_UNK func_80158EE4();                            /* static */
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8015E5D8;
extern M2C_UNK D_8015E648;
extern M2C_UNK D_8015E668;

void func_8015A8E4(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_a1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s4;
    s8 var_v0_2;
    s8 var_v1;
    u8 *var_s1;
    u8 temp_v1;
    void *temp_v1_3;
    void *var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    var_s4 = 0;
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        var_s1 = NULL;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            switch (temp_v0) {                      /* switch 2 */
            case 7:                                 /* switch 2 */
                var_s4 = 1;
                goto block_13;
            case 6:                                 /* switch 2 */
                var_s4 = 1;
                goto block_14;
            case 5:                                 /* switch 2 */
                var_s4 = 1;
                goto block_15;
            }
        } else {
            temp_v1_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            switch (temp_v1_2) {                    /* switch 3; irregular */
            case 3:                                 /* switch 3 */
            case 3:                                 /* switch 2 */
block_13:
                var_s1 = arg3 + 0xE;
                break;
            case 2:                                 /* switch 3 */
            case 2:                                 /* switch 2 */
block_14:
                var_s1 = arg3 + 0xB;
                break;
            case 1:                                 /* switch 3 */
            case 1:                                 /* switch 2 */
block_15:
                var_s1 = arg3 + 8;
                break;
            }
        }
        if (*var_s1 != 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
            if (var_s4 != 0) {
                var_v0 = D_800814A8;
                M2C_FIELD(arg3, void **, 0x60) = var_v0;
                goto block_21;
            }
            if (M2C_FIELD(((*var_s1 * 0x14) + &D_8006DE24), u8 *, 0x12) == 2) {
                var_v0 = M2C_FIELD(arg3, void **, 0x60);
                if (var_v0 != NULL) {
block_21:
                    temp_v1_3 = M2C_FIELD(var_v0, void **, -0x14);
                    M2C_FIELD(arg3, s8 *, 0x72) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x24);
                    M2C_FIELD(arg3, s8 *, 0x73) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x25);
                }
            } else {
                M2C_FIELD(arg3, void **, 0x60) = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
                var_v0_2 = M2C_FIELD(arg3, s8 *, 0x72);
                var_v1 = M2C_FIELD(arg3, s8 *, 0x73);
                if (var_v0_2 < 0) {
                    var_v0_2 = -var_v0_2;
                }
                if (var_v1 < 0) {
                    var_v1 = -var_v1;
                }
                M2C_FIELD(arg3, s8 *, 0x72) = var_v0_2;
                M2C_FIELD(arg3, s8 *, 0x73) = var_v1;
            }
            if (func_800A94A0(arg3, var_s1, var_s4, arg0 + 0x98) != 0) {
                func_800BB044(arg3);
block_43:
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                return;
            }
        } else {
        default:                                    /* switch 1 */
            return;
        }
        break;
    case 1:                                         /* switch 1 */
        if (func_8003F270() != 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 2:                                         /* switch 1 */
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_8015E648;
block_42:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
            goto block_43;
        }
        break;
    case 3:                                         /* switch 1 */
        if (((M2C_FIELD(arg2, s8 *, 4) == 6) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
        }
        if ((M2C_FIELD(arg0, u16 *, 0x98) & 0x80) && (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            var_a1 = &D_8015E668;
            goto block_42;
        }
        break;
    case 4:                                         /* switch 1 */
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015E5D8;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015E5D8), 0);
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80158EE4;
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, s8 *, 0x73) = 0;
            M2C_FIELD(arg3, s8 *, 0x72) = 0;
            M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            func_800A56E0(0xB4);
        }
        break;
    }
}
