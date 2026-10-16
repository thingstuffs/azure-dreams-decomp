#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_801269F8;

void func_80125694(void *arg0) {
    M2C_FIELD(&D_801269F8, u8 *, 9) = (u8) (M2C_FIELD(&D_801269F8, u8 *, 9) + 4);
    if (!(M2C_FIELD(&D_801269F8, u8 *, 9) & 0xF)) {
        M2C_FIELD(arg0, s8 *, 0xA) = 8;
    }
}
