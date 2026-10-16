#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047320(void *, u8, s8, u8);          /* extern */
M2C_UNK func_800A86C4(void *);                      /* extern */
M2C_UNK func_8016ABE0(void *, void *, void *);      /* extern */
extern M2C_UNK D_8016CE94;
extern void *D_8016D714;
extern u16 D_8016D718;

s32 func_8016CD6C(void *arg0, void *arg2) {
    s32 temp_t0;
    s32 temp_v1;
    u16 temp_v0;
    u8 temp_a3;

    temp_a3 = M2C_FIELD(D_8016D714, u8 *, 1);
    temp_t0 = temp_a3 & 0xFF;
    if (temp_t0 == 0) {
        M2C_FIELD(arg0, s8 *, 0xBA) = 0;
        goto block_11;
    }
    temp_v0 = D_8016D718 + 1;
    D_8016D718 = temp_v0;
    if ((s32) M2C_FIELD(D_8016D714, u8 *, 0) < (s16) temp_v0) {
        D_8016D714 += 2;
        D_8016D718 = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    }
    M2C_FIELD(arg0, s16 *, 0x2A) = (s16) ((temp_a3 & 7) << 9);
    M2C_FIELD(arg0, u16 *, 0x46) = (u16) (M2C_FIELD(arg0, u16 *, 0x46) | 0x8000);
    temp_v1 = temp_t0 & 0xF8;
    switch (temp_v1) {                              /* irregular */
    case 8:
        func_8016ABE0(arg0, arg2, arg0);
        return 0;
    case 16:
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8016CE94) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016CE94;
            func_80047320(arg2, *((((s32) (*(s16 *)0x800848E0 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016CE94), M2C_FIELD(arg2, s8 *, 4), temp_a3);
        }
block_11:
        func_800A86C4(arg0);
        return 0;
    }
}
