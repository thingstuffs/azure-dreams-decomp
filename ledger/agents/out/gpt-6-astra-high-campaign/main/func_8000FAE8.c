#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8002290C();                         /* extern */
M2C_UNK func_80022A30();                    /* extern */

/* Processes the embedded data and then updates the record. */
void func_80022AE8(s32 record) {
    func_80022A30(record + 0x24, record);
    func_8002290C(record);
}
