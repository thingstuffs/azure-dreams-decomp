#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AB538();                            /* extern */

void func_8016D030(void *arg0) {
    func_800AB538();
    M2C_FIELD(arg0, s16 *, 0xA6) = 0;
}
