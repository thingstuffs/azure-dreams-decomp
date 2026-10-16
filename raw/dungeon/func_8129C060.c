#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003500C(M2C_UNK *);                   /* extern */
extern M2C_UNK D_80154FC8;

void func_80154860(void *arg0, void *arg3) {
    if (*(s32 *)0x80084828 & 0x200000) {
        func_8003500C(&D_80154FC8);
        M2C_FIELD(arg3, s8 *, 0x6D) = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    }
}
