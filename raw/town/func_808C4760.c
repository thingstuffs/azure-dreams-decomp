#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_00000710;
extern M2C_UNK D_0000071C;
extern M2C_UNK D_00000724;
extern M2C_UNK D_0000072C;

void func_80000760(s32 arg0) {
    M2C_FIELD(*(void **)0xE68, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_00000710, &D_0000071C, arg0);
    M2C_FIELD(*(void *)0xE68, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_00000710, &D_00000724, *(s32 *)0xDA0);
    M2C_FIELD(*(void *)0xE68, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_00000710, &D_0000072C, *(s32 *)0xD9C);
}
