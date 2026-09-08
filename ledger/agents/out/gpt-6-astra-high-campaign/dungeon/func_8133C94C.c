#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003F80C(); /* extern */
extern M2C_UNK D_80173DBC;

/* Initializes the global resource with size 0x7AC0 and options 1 and 2. */
void func_8017394C(void) {
    func_8003F80C(&D_80173DBC, 0x7AC0, 1, 2);
}
