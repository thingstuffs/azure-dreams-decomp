#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_00000630;
extern M2C_UNK D_0000063C;
extern M2C_UNK D_00000644;
extern M2C_UNK D_0000064C;

void func_800006C4(s32 arg0) {
    M2C_FIELD(*(void **)0x1040, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_00000630, &D_0000063C, arg0);
    M2C_FIELD(*(void *)0x1040, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_00000630, &D_00000644, *(s32 *)0xF0C);
    M2C_FIELD(*(void *)0x1040, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s32), 0x64)(&D_00000630, &D_0000064C, *(s32 *)0xF08);
}
