#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80023600();                         /* extern */
M2C_UNK func_80023730();               /* extern */
M2C_UNK func_8002388C();                            /* extern */

/* Prepares processing, processes the embedded data, and updates the record. */
void func_80023894(s32 record) {
    func_8002388C();
    func_80023730(record + 0x190, record + 0x168, record + 0x178);
    func_80023600(record);
}
