#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001EAA4(s8 *, s8 *);                  /* extern */
s32 func_80033BC0(M2C_UNK);                         /* extern */
s32 func_800A697C(M2C_UNK, M2C_UNK);                /* extern */
extern u8 D_8001F6F0;
extern s16 D_8008146C;
extern void *D_800E3D7C;

u8 func_8001E660(s8 *arg0, s8 *arg1, s32 arg3) {
    s8 var_v1;

    if ((D_8001F6F0 == 0) && (arg3 == 0) && (*(s32 *)0x80012090 == 0)) {
        switch (D_8008146C) {                       /* irregular */
        case 12:
            if (M2C_FIELD(D_800E3D7C, u8 *, 0xFB) == 0) {
                *arg0 = (s8) D_8008146C;
                var_v1 = 4;
block_21:
                *arg1 = var_v1;
                D_8001F6F0 = 1;
                return 1U;
            }
            goto block_23;
        case 15:
            if ((func_80033BC0(0x145E) != 0) && (func_80033BC0(0x1460) == 0) && ((func_800A697C(0xD, 1) << 0x10) == 0)) {
                *arg0 = 0xD;
                *arg1 = 1;
                D_8001F6F0 = 1;
                return 1U;
            }
            goto block_23;
        case 28:
            if ((func_80033BC0(0xFC3) != 0) && (func_80033BC0(0xFAD) == 0) && ((func_800A697C(1, 8) << 0x10) == 0)) {
                *arg0 = 1;
                *arg1 = 8;
                D_8001F6F0 = 1;
                return 1U;
            }
            goto block_23;
        case 20:
            if ((func_80033BC0(0xAC) != 0) && (func_80033BC0(0x12C6) == 0) && ((func_800A697C(0xD, 6) << 0x10) == 0)) {
                *arg0 = 0xD;
                var_v1 = 6;
                goto block_21;
            }
            goto block_23;
        }
    } else {
block_23:
        func_8001EAA4(arg0, arg1);
        return 0U;
    }
}
