#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AB538();                            /* extern */

void func_80155C40(void *arg0) {
    func_800AB538();
    M2C_FIELD(arg0, s16 *, 0xA6) = 0;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA8) = (s32) M2C_FIELD(arg0, s32 *, 0xA4);
}
