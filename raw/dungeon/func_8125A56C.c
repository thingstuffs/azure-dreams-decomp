#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, s8, u8);          /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_8016BBE0(void *, void *, void *);      /* extern */
extern M2C_UNK D_8016DE94;
extern void *D_8016E714;
extern u16 D_8016E718;

s32 func_8016DD6C(void *arg0, void *arg2) {
    s32 temp_t0;
    s32 temp_v1;
    u16 temp_v0;
    u8 temp_a3;

    temp_a3 = M2C_FIELD(D_8016E714, u8 *, 1);
    temp_t0 = temp_a3 & 0xFF;
    if (temp_t0 == 0) {
        M2C_FIELD(arg0, s8 *, 0xBA) = 0;
        goto block_11;
    }
    temp_v0 = D_8016E718 + 1;
    D_8016E718 = temp_v0;
    if ((s32) M2C_FIELD(D_8016E714, u8 *, 0) < (s16) temp_v0) {
        D_8016E714 += 2;
        D_8016E718 = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    }
    M2C_FIELD(arg0, s16 *, 0x2A) = (s16) ((temp_a3 & 7) << 9);
    M2C_FIELD(arg0, u16 *, 0x46) = (u16) (M2C_FIELD(arg0, u16 *, 0x46) | 0x8000);
    temp_v1 = temp_t0 & 0xF8;
    switch (temp_v1) {                              /* irregular */
    case 8:
        func_8016BBE0(arg0, arg2, arg0);
        return 0;
    case 16:
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8016DE94) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016DE94;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016DE94), M2C_FIELD(arg2, s8 *, 4), temp_a3);
        }
block_11:
        func_800A9A0C(arg0);
        return 0;
    }
}
