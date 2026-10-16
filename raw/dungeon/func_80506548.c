#include "common.h"
#include "m2c_compat.h"

void func_8001DD48(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 4) > 0) {
        M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) - 1);
        M2C_FIELD(arg0, s16 *, 4) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 4) - 1);
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) - 0x20);
    }
}
