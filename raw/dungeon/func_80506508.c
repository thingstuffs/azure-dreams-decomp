#include "common.h"
#include "m2c_compat.h"

void func_8001DD08(void *arg0) {
    if ((u16) M2C_FIELD(arg0, u16 *, 4) < 9U) {
        M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) + 1);
        M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 0x20);
    }
}
