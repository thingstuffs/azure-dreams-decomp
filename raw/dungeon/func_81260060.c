#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800353F4(M2C_UNK *);                   /* extern */
extern M2C_UNK D_80167FC8;

void func_80167860(void *arg0, void *arg3) {
    if (*(s32 *)0x80083170 & 0x200000) {
        func_800353F4(&D_80167FC8);
        M2C_FIELD(arg3, s8 *, 0x6D) = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    }
}
