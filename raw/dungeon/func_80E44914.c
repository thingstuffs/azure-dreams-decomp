#include "common.h"
#include "m2c_compat.h"

s32 func_800A2BDC(void *);                          /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
s16 func_800ADDA0(M2C_UNK, M2C_UNK, void *, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_801656A4(void *, M2C_UNK, M2C_UNK, void *); /* extern */

s32 func_80166114(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v0;
    s32 var_v0;

    temp_v0 = func_800ADDA0(arg1, arg2, arg0, 2, 4, arg0 + 0x9C);
    var_v0 = 0;
    if (temp_v0 >= 0) {
        switch (temp_v0) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
            func_800A9A0C(arg0);
            return 0;
        case 2:
            func_801656A4(arg0, arg1, arg2, arg0);
            return 0;
        case 1:
            M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
            if ((func_800A2BDC(arg0) << 0x10) == 0) {
            default:
                M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
                var_v0 = 1;
                if (*(u16 *)0x80083462 & 8) {
                    goto block_11;
                }
            } else {
block_11:
                var_v0 = 0;
                M2C_FIELD(arg0, u16 *, 0x46) = (u16) (M2C_FIELD(arg0, u16 *, 0x46) & 0x7FFF);
            }
            /* Duplicate return node #12. Try simplifying control flow for better match */
            return var_v0;
        }
    } else {
        return var_v0;
    }
}
