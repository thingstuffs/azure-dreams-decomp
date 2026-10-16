#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047320(void *, u8, M2C_UNK);         /* extern */
s32 func_80098F70(void *, s32);                     /* extern */
s32 func_800A1904(void *, M2C_UNK);                 /* extern */
M2C_UNK func_800A86BC(void *);                      /* extern */
M2C_UNK func_800A86C4(void *);                      /* extern */
M2C_UNK func_800A8F10(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800A936C(void *, M2C_UNK, void *, M2C_UNK); /* extern */
M2C_UNK func_800A9540(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_801666B8(void *, M2C_UNK, void *, void *); /* extern */
extern M2C_UNK D_80085990;
extern M2C_UNK D_80164514;
extern M2C_UNK D_80166EC4;
extern M2C_UNK D_80166ECC;

void func_80166364(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 temp_v1_2;
    u16 temp_v1_3;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) - 1);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80166EC4;
            func_80047320(arg2, *((((s32) (*(s16 *)0x800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80166EC4), 0);
block_23:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80166ECC;
            func_80047320(arg2, *((((s32) (*(void *)0x800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80166ECC), 0);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) + 1);
            goto block_23;
        }
        if (!(M2C_FIELD(&D_80085990, u16 *, 2) & 0x1000) && ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800A936C(arg0, arg1, arg2, 0) == 0)) && ((func_800A1904(arg3) << 0x10) == 0)) {
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
                M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) - temp_v1_3);
                func_801666B8(arg0, arg1, arg2, arg3);
                return;
            }
            if ((M2C_FIELD(arg3, s8 *, 0x6D) != 0) && (((func_800A1904(arg3, arg1) << 0x10) == 0) || ((func_80098F70(arg3, M2C_FIELD(*(void **)0x800803DC, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
                func_800A86C4(arg3);
                func_800A86BC(arg3);
                if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
                    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80166ECC;
                    func_80047320(arg2, *((((s32) (*(void *)0x800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80166ECC), 0);
                    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
                    M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) + 1);
                    goto block_23;
                }
            }
        }
        break;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) - 1);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & ~8);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164514;
        }
        break;
    }
}
