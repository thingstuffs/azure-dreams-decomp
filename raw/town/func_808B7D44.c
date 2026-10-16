#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_000034B0;
extern M2C_UNK D_000034BC;
extern M2C_UNK D_000034C4;
extern M2C_UNK D_000034CC;

void func_80003544(s32 arg0) {
    M2C_FIELD(*(void **)0x4610, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_000034B0, &D_000034BC, arg0);
    M2C_FIELD(*(void *)0x4610, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_000034B0, &D_000034C4, *(s32 *)0x3F54);
    M2C_FIELD(*(void *)0x4610, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_000034B0, &D_000034CC, *(s32 *)0x3F50);
}
