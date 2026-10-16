#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A3784(M2C_UNK);                     /* extern */
s32 func_800A9E78();                                /* extern */
M2C_UNK func_800AC24C(M2C_UNK, M2C_UNK);            /* extern */
s32 func_800AC66C(M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_80158514;

void func_80159474(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    if (func_800A9E78() != 0) {
        func_800AC24C(arg3, 0);
        func_800A3784(arg3);
        if ((func_800AC66C(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80158514;
            goto block_3;
        }
    } else {
block_3:
        if (*(u16 *)0x80085992 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x92) = -0x20;
        }
    }
}
