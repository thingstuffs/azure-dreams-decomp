#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AB538();                            /* extern */

void func_8014F42C(void *arg0) {
    func_800AB538();
    M2C_FIELD(arg0, s16 *, 0xB6) = 0;
}
