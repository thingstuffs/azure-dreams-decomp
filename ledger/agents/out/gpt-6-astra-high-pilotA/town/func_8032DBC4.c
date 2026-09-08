#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B54();                /* extern */
M2C_UNK func_80019BC0();                            /* extern */
M2C_UNK func_8001ACE8();                     /* extern */
s32 func_8001B0C8();                                /* extern */

/* Sets conditional and fixed flags, then applies the selected record entry. */
void func_800183C4(s32 record, M2C_UNK entry_index) {
    if (func_8001B0C8() >= 5) {
        func_80019BC0();
    }
    func_8001ACE8(0xD7F);
    func_80019B54(record, entry_index);
}
