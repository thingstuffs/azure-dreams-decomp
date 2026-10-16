#include "common.h"
#include "m2c_compat.h"

s32 func_800424C4(M2C_UNK *, M2C_UNK);              /* extern */
M2C_UNK func_8004272C(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_80047320(void *, u8, M2C_UNK);         /* extern */
s32 func_80098F70(M2C_UNK *, s32);                  /* extern */
s16 func_8009EB30(M2C_UNK *, void *);               /* extern */
s32 func_800A1904(M2C_UNK *, M2C_UNK);              /* extern */
s32 func_800A59E8(M2C_UNK *);                       /* extern */
M2C_UNK func_800A86BC(M2C_UNK *);                   /* extern */
M2C_UNK func_800A86C4(M2C_UNK *);                   /* extern */
M2C_UNK func_800A8F10(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
s32 func_800A936C(void *, M2C_UNK, void *, M2C_UNK); /* extern */
M2C_UNK func_800A9454(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800A9540(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_80164514();                            /* static */
M2C_UNK func_801666B8(void *, M2C_UNK, void *, M2C_UNK *); /* static */
extern void *D_800803DC;
extern M2C_UNK D_80081490;
extern s16 D_800848E0;
extern M2C_UNK D_80085990;
extern M2C_UNK D_80166E94;
extern M2C_UNK D_80166EBC;
extern M2C_UNK D_80166EC4;
extern M2C_UNK D_80166ECC;

void func_80165EC4(void *arg0, M2C_UNK arg1, void *arg2, M2C_UNK *arg3) {
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
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80166E94;
            func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80166E94), 0);
            M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) - 1);
            var_v0 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_36:
            M2C_FIELD(arg0, u8 *, 0x9B) = var_v0;
            return;
        }
    default:
        return;
    case 1:
        if (M2C_FIELD(arg0, s16 *, 0x92) == 0) {
            var_a1 = &D_80166EBC;
block_35:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
            func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            var_v0 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
            goto block_36;
        }
        break;
    case 2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0 + 1);
        if ((s16) temp_v0 >= 2) {
            var_a1 = &D_80166EC4;
            goto block_35;
        }
        break;
    case 3:
        if ((func_800424C4(arg3, 1) << 0x10) != 0) {
            if (!(M2C_FIELD(&D_80085990, u16 *, 2) & 0x1000) && ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800A936C(arg0, arg1, arg2, 0) == 0))) {
                if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
                    if (!(M2C_FIELD(&D_80085990, u16 *, 2) & 0x2008)) {
                        func_800A9454(arg0, arg1, arg2, arg3);
                        return;
                    }
                } else if ((func_800A1904(arg3) << 0x10) == 0) {
                    temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
                    if (temp_v1_2 & 0x100) {
                        func_800A8F10(arg0, arg1, arg2, arg3);
                        return;
                    }
                    if (temp_v1_2 & 0x80000) {
                        func_800A9540(arg0, arg1, arg2, arg3);
                        temp_v1_3 = M2C_FIELD(arg0, u16 *, 0xA2);
                        M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
                        M2C_FIELD(arg0, s16 *, 0x9E) = 0;
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) - temp_v1_3);
                        func_801666B8(arg0, arg1, arg2, arg3);
                        return;
                    }
                    if ((M2C_FIELD(arg3, s8 *, 0x6D) != 0) && (((func_800A1904(arg3, arg1) << 0x10) == 0) || ((func_80098F70(arg3, M2C_FIELD(D_800803DC, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
                        func_800A86C4(arg3);
                        func_800A86BC(arg3);
                        if ((func_800424C4(arg3, 1) << 0x10) != 0) {
                            var_a0 = &D_80081490;
                            temp_v1_4 = M2C_FIELD(arg2, s8 *, 0x26);
                            if ((((temp_v1_4 == M2C_FIELD(&D_80081490, s8 *, 0x26)) && (temp_v1_4 >= 0)) || (var_a0 = arg3, ((func_8009EB30(&D_80081490, arg2) < 2) != 0))) && !(func_800A59E8(var_a0) & 7)) {
                                func_8004272C(arg3, 1);
                            }
                        }
                        if ((func_800424C4(arg3, 1) << 0x10) == 0) {
                            goto block_31;
                        }
                    }
                }
            }
        } else {
block_31:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80166ECC;
            func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80166ECC), 0);
            if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) + 1);
                return;
            }
block_39:
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80164514;
        }
        break;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_80166E94;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            goto block_35;
        }
        break;
    case 5:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_2 + 1);
        if ((s16) temp_v0_2 >= 4) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80166E94;
            func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80166E94), 0);
            M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) - 1);
            goto block_39;
        }
        break;
    }
}
