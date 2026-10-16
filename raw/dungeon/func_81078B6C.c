#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A4ACC(M2C_UNK);                     /* extern */
s32 func_800AB1C0();                                /* extern */
M2C_UNK func_800AD594(M2C_UNK, M2C_UNK);            /* extern */
s32 func_800AD9B4(M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_80152F68;

void func_8015436C(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    if (func_800AB1C0() != 0) {
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80152F68;
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            goto block_3;
        }
    } else {
block_3:
        if (*(u16 *)0x80083462 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x92) = 0;
        }
    }
}
