#include "common.h"
#include "m2c_compat.h"

s32 func_800A2BDC(void *);                          /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
s16 func_800ADDA0(M2C_UNK, M2C_UNK, void *, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8015FBE0(void *, M2C_UNK, M2C_UNK, void *); /* extern */

s32 func_80160330(void *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    s16 temp_v0;
    s32 var_v0;

    temp_v0 = func_800ADDA0(arg1, arg2, arg0, 3, 6, arg0 + 0x9C);
    var_v0 = 0;
    if (temp_v0 >= 0) {
        if ((arg3 << 0x10) == 0) {
            switch (temp_v0) {                      /* irregular */
            case 0:
                M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
                func_800A9A0C(arg0);
                return 0;
            case 1:
                M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
                if ((func_800A2BDC(arg0) << 0x10) == 0) {
                default:
                    M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
                    var_v0 = 1;
                    if (*(u16 *)0x80083462 & 8) {
                        goto block_12;
                    }
                } else {
block_12:
                    var_v0 = 0;
                    M2C_FIELD(arg0, u16 *, 0x46) = (u16) (M2C_FIELD(arg0, u16 *, 0x46) & 0x7FFF);
                }
                /* Duplicate return node #13. Try simplifying control flow for better match */
                return var_v0;
            }
        } else {
        case 2:
            func_8015FBE0(arg0, arg1, arg2, arg0);
            return 0;
        }
    } else {
        return var_v0;
    }
}
