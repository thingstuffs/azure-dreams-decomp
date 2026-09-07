#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008C214();                      /* extern */
extern u8 D_800FC428;

void func_8008C28C(s32 arg0) {
    func_8008C214(arg0, (arg0 << 6) + &D_800FC428);
}
